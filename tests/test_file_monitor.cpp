#include "skyrpc/log.h"
#include "skyrpc/file_monitor.h"
using namespace skyrpc;
int main() {

    FileMonitor fileMonitor;
    fileMonitor.addFileWatch("/home/zavier/log", FileMonitor::ALL,
                             [](FileMonitor::EventContext ctx){
        LOG_DEBUG << "log file modify";
    });

    fileMonitor.addDirectoryWatch("/home/zavier/tmp", FileMonitor::ALL,
                              [](std::vector<FileMonitor::EventContext> vec){
        for(auto e: vec) {
          LOG_DEBUG << e.path;
        }
    });

    sleep(100);

}