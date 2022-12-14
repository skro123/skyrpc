#include "skyrpc/log.h"
#include "skyrpc/net/uri.h"

namespace skyrpc {
static skyrpc::Logger::ptr g_logger = SKYRPC_LOG_ROOT();

Uri::Uri()
        : m_port(0)
        , m_cur(nullptr){

}

Uri::ptr Uri::Create(const std::string &uri) {
    if (uri.empty()) {
        return nullptr;
    }
    Uri::ptr res(new Uri);

    Task<bool> parse_task = res->parse();
    for (size_t i = 0; i < uri.size(); ++i) {
        res->m_cur = &uri[i];
        parse_task.resume();
        if (!parse_task.get()) {
            return nullptr;
        }
    }
    res->m_cur = nullptr;
    parse_task.resume();

    if (!parse_task.get()) {
        return nullptr;
    }
    return res;
}

Address::ptr Uri::createAddress() {
    IPAddress::ptr addr = Address::LookupAnyIPAddress(m_host);
    if (addr) {
        addr->setPort(getPort());
    }
    return addr;
}
const std::string& Uri::getPath() const {
    static std::string default_path = "/";
    if (m_scheme == "magnet") {
        return m_path;
    }
    return m_path.empty() ? default_path : m_path;
}

uint32_t Uri::getPort() const {
    if(m_port) {
        return m_port;
    }
    if(m_scheme == "http" || m_scheme == "ws") {
        return 80;
    } else if(m_scheme == "https" || m_scheme == "wss") {
        return 443;
    }
    return m_port;
}

/*
 foo://user@hostname:8080/over/there?name=ferret#nose
   \_/   \______________/\_________/ \_________/ \__/
    |           |            |            |        |
 scheme     authority       path        query   fragment
*/
std::ostream &Uri::dump(std::ostream &ostream) {
    ostream << m_scheme ;
    if (m_scheme.size()) {
        ostream << ':';
        if (m_scheme != "magnet") {
            ostream << "//";
        }
    }
    ostream << m_userinfo << (m_userinfo.empty()? "" : "@")
            << m_host
            << (isDefaultPort()? "" : ":" + std::to_string(m_port))
            << getPath()
            << (m_query.empty()? "" : "?") << m_query
            << (m_fragment.empty()? "" : "#") << m_fragment;
    return ostream;
}

std::string Uri::toString() {
    std::stringstream ss;
    dump(ss);
    return ss.str();
}

bool Uri::isDefaultPort() const {
    if(m_port == 0) {
        return true;
    }
    if(m_scheme == "http" || m_scheme == "ws") {
        return m_port == 80;
    } else if(m_scheme == "https" || m_scheme == "wss") {
        return m_port == 443;
    }
    return false;
}


/**
* ??????URI????????????????????????, O(1)???????????????
* @param p
* @return bool
*/
static inline bool IsValid(const char* p) {
    char c = *p;
    /// RFC3986???????????????Url??????????????????????????????a-zA-Z???????????????0-9??????-_.~4??????????????????????????????????????????????????????
    ///  ! * ' ( ) ; : @ & = + $ , / ? # [ ]?????????????????????????????????

    switch (c) {
        case 'a'...'z':
        case 'A'...'Z':
        case '0'...'9':
        case '-':
        case '_':
        case '.':
        case '~':
        case '!':
        case '*':
        case '\'':
        case '(':
        case ')':
        case ';':
        case ':':
        case '@':
        case '&':
        case '=':
        case '+':
        case '$':
        case ',':
        case '/':
        case '?':
        case '#':
        case '[':
        case ']':
        case '%':
            return true;
        default:
            return false;
    }
}

#define yield \
co_yield true;  \
if(!m_cur) {    \
    co_return false;\
}

/**
* ??????uri??????
*      foo://user@hostname.com:8080/over/there?name=ferret#nose
*        \_/   \__________________/\_________/ \_________/ \__/
*        |           |                |            |        |
*     scheme     authority          path        query   fragment
* URI????????????
* ([]??????????????????)
* [ scheme : ] scheme-specific-part[ # fragment]
* ??????scheme-specific-part?????????????????????//????????????
*  [ //][ authority][ path][ ? query]
*  ??????authority????????????,???????????????URI?????????authority?????????????????????host??????
* [ user-info @] host [ : port]
* ??????URI????????????
* [ scheme :][ user-info @] host [ : port][ path][ ? query][ # fragment]
*/
Task<bool> Uri::parse() {
    size_t port_idx = 0;
    std::string buff;
    while (*m_cur != ':' && *m_cur != '?' && *m_cur != '#' && *m_cur != '/' && IsValid(m_cur)) {
        buff.push_back(*m_cur);
        co_yield true;
        if (!m_cur) {
            m_host = std::move(buff);
            co_return true;
        }
    }
    if (*m_cur == '/') {
        /// ?????? host
        m_host = std::move(buff);
        goto parse_path;
    }
    yield;
    if (isdigit(*m_cur)) {
        /// ?????? host
        m_host = std::move(buff);
        goto parse_port;
    }

    m_scheme = std::move(buff);

    /// ?????? [ // ]
    if (*m_cur == '/'){
        yield;
        if (*m_cur != '/'){
            co_return false;
        }
        yield;
        /// ?????? authority, ???????????????URI?????????authority?????????????????????host??????
        /// [ user-info @] host [ : port]

        if (*m_cur != '/') {
            while (*m_cur != '@'  && *m_cur != '/' && IsValid(m_cur)) {
                buff.push_back(*m_cur);
                if (*m_cur == ':' && !port_idx) {
                    port_idx = buff.size();
                }
                co_yield true;
                if (!m_cur) {
                    if (port_idx) {
                        m_host = buff.substr(0, port_idx-1);
                        try {
                            m_port = std::stoul(buff.substr(port_idx));
                        } catch (...) {
                            co_return false;
                        }
                        buff.clear();
                    } else {
                        m_host = std::move(buff);
                    }
                    co_return true;
                }
            }
            if (buff.empty() || !IsValid(m_cur)) {
                co_return false;
            }

            /// ?????? userinfo
            if (*m_cur == '@') {
                port_idx = 0;
                m_userinfo = std::move(buff);
                yield;
                while (*m_cur != ':' && *m_cur != '/' && IsValid(m_cur)) {
                    buff.push_back(*m_cur);
                    co_yield true;
                    if (!m_cur) {
                        m_host = std::move(buff);
                        co_return true;
                    }
                }
                if (buff.empty() || !IsValid(m_cur)) {
                    co_return false;
                }

                /// ?????? host
                m_host = std::move(buff);
                /// ?????? port
                if (*m_cur == ':') {
                    yield;
                    parse_port:
                    while (isdigit(*m_cur)) {
                        buff.push_back(*m_cur);
                        co_yield true;
                        if (!m_cur) {
                            try {
                                m_port = std::stoul(buff);
                                co_return true;
                            } catch (...) {
                                co_return false;
                            }
                        }
                    }
                    if (*m_cur != '/' || buff.empty()) {
                        co_return false;
                    }
                    try {
                        m_port = std::stoul(buff);
                    } catch (...) {
                        co_return false;
                    }
                    buff.clear();
                }
            } else {
                if (port_idx) {
                    m_host = buff.substr(0, port_idx-1);
                    try {
                        m_port = std::stoul(buff.substr(port_idx));
                    } catch (...) {
                        co_return false;
                    }
                    buff.clear();
                } else {
                    m_host = std::move(buff);
                }

            }

        }
        /// ?????? path
        if (*m_cur == '/') {
            parse_path:
            buff.push_back('/');
            co_yield true;
            if (!m_cur) {
                m_path = std::move(buff);
                co_return true;
            }
            while (*m_cur != '?' && *m_cur != '#' && IsValid(m_cur)) {
                buff.push_back(*m_cur);
                co_yield true;
                if (!m_cur) {
                    m_path = std::move(buff);
                    co_return true;
                }
                if (!IsValid(m_cur)) {
                    co_return false;
                }
            }
            m_path = std::move(buff);
        }
    }

    /// ?????? query
    if (*m_cur == '?') {
        yield;
        while (*m_cur != '#' && IsValid(m_cur)) {
            buff.push_back(*m_cur);
            co_yield true;
            if (!m_cur) {
                m_query = std::move(buff);
                co_return true;
            }
            if (!IsValid(m_cur)) {
                co_return false;
            }
        }
        m_query = std::move(buff);
    }
    /// ?????? fragment
    if (*m_cur == '#') {
        yield;
        while (IsValid(m_cur)) {
            buff.push_back(*m_cur);
            co_yield true;
            if (!m_cur) {
                m_fragment = std::move(buff);
                co_return true;
            }
            if (!IsValid(m_cur)) {
                co_return false;
            }
        }
        m_fragment = std::move(buff);
    }
    co_return false;
}

}