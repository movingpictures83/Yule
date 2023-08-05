#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "YulePlugin.h"

void YulePlugin::input(std::string file) {
 inputfile = file;
}

void YulePlugin::run() {

}

void YulePlugin::output(std::string file) {
   std::string command = "export OLDPATH=${PATH}; ";
   command += "export PATH=${CONDA_HOME}/bin/:${PATH}; ";
   command += "eval \"$(conda shell.bash hook)\"; ";
   command += "conda activate qiime2-2021.4; ";
   command += "qiime diversity beta --i-table "+inputfile+" --p-metric yule --o-distance-matrix "+file+"; unzip -jo "+file+" -d "+PluginManager::prefix()+"; ";
   command += "conda deactivate; ";
   command += "export PATH=${OLDPATH}";
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<YulePlugin> YulePluginProxy = PluginProxy<YulePlugin>("Yule", PluginManager::getInstance());
