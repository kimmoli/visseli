/*
    visseli, Visseli
*/

#ifndef MORSE_H
#define MORSE_H
#include <QObject>
#include "qmultimediaaudiorecorder.h"
#include "generator.h"
#include <AudioResourceQt>

class Morse : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ readVersion NOTIFY versionChanged())
    Q_PROPERTY(bool initialised READ readInitialised NOTIFY initialisedChanged())
    Q_PROPERTY(int vuValue READ readVuValue NOTIFY vuValueChanged())

public:
    explicit Morse(QObject *parent = 0);
    ~Morse();

    Q_INVOKABLE void init();
    Q_INVOKABLE void rec();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void beep();

    QString readVersion();
    bool readInitialised() { return _initialised; }
    int readVuValue() { return _vuValue; }

private slots:
    void vuMeterValueUpdate(float value);
    void audioAcquired();

signals:
    void versionChanged();
    void initialisedChanged();
    void vuValueChanged();

private:
    QMultimediaAudioRecorder *mmar;
    Generator *gen;
    bool _initialised;
    bool _playing;
    int _vuValue;
    QAudioFormat _format;
    QAudioOutput *_audioOutput;
    AudioResourceQt::AudioResource _audio_resource;

};


#endif // MORSE_H

