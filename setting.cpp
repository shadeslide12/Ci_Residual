#include "setting.h"

Setting::Setting() {
    runCore = 4;
    workDir = " ";
    cipherPath = " ";
    pressureList = {};
}

void Setting::setWorkDir(const QString& dir) {
    workDir = dir;
}

void Setting::setCipherDir(const QString &path) {
    cipherPath = path;
}

void Setting::setRunCore(int core) {
    runCore = core;
}

void Setting::addPressure(double pressure) {
    pressureList.append(pressure);
}

void Setting::clearPressure() {
    pressureList.clear();
}

QString Setting::getWorkDir() const {
    return workDir;
}

QString Setting::getCipherPath() const {
    return  cipherPath;
}

int Setting::getRunCore() const {
    return runCore;
}
