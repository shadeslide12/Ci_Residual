#ifndef QTTEST_CIPHERRUNNER_H
#define QTTEST_CIPHERRUNNER_H

#include <QObject>
#include <QProcess>

class CipherRunner: public QObject{
Q_OBJECT

public:
    explicit CipherRunner(QWidget* parent= nullptr);

    void runCipher();
    void updateLogger();
    void recordError();
signals:
    void messageToLog(const QByteArray& message);
    void errorToLog(const QByteArray& error);
    void finished();
private:
    QProcess* pro_cipher;

};


#endif //QTTEST_CIPHERRUNNER_H
