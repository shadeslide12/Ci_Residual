#ifndef QTTEST_SETTING_H
#define QTTEST_SETTING_H

#include <QString>
#include <QVector>

class Setting{

public:
    explicit Setting();

    void setWorkDir(const QString& dir);
    void setCipherDir(const QString& path);
    void setRunCore(int core);
    void addPressure(double pressure);
    void clearPressure();

    QString getWorkDir() const;
    QString getCipherPath() const;
    int getRunCore() const;

private:
    QString workDir;
    QString cipherPath;
    int runCore;
    QVector<double> pressureList;

};


#endif //QTTEST_SETTING_H
