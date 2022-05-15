#ifndef LETTERSYSTEM_H
#define LETTERSYSTEM_H

#include <QObject>
#include "staffinfomanager.h"
#include "letterinfomanager.h"
#include "sendinfomanager.h"
#include "receiveinfomanager.h"
class LetterSystem : public InfoManager
{
    Q_OBJECT
public:
    explicit LetterSystem(const QString& staff_cnn="staffcnn_ls",const QString& letter_cnn = "lettercnn_ls",
                          const QString& receive_cnn="receivecnn_ls",const QString&send_cnn = "sendcnn_ls");

    bool FetchSentLetterTitles(const unsigned int staffid,QList<QString>& titles);
    bool FetchReceivedLetterTitles(const unsigned int staffid,QList<QString>& titles);
    bool FetchALetterSender(const unsigned int letterid,QString& sender);
    bool FetchALetterReceiver(const unsigned int letterid,QList<QString>& receiver);
    bool FetchALetterContent(const unsigned int letterid,QString& content);
    bool FetchALetterState(const unsigned int letterid,LetterState& state);
    bool FetchALetterTitle(const unsigned int letterid, QString &title);
    bool StarALetter(const unsigned int letterid);
    bool ReadALetter(const unsigned int letterid);
    bool UnreadALetter(const unsigned int letterid);
    bool SendALetter(const unsigned int sender, const unsigned int receiver, const QString& content, const QString &title, const QString datetime);
    //becareful: only if both sender and receiver delete the letter then the letter can be removed from database
    bool DeleteALetterAsASender(const unsigned int letterid,const unsigned int staffid);
    bool DeleteALetterAsAReceiver(const unsigned int letterid,const unsigned int staffid);
    bool DeleteSender(const unsigned int senderid);
    bool DeleteReceiver(const unsigned int receiverid);
    bool FetchSentLetters(const unsigned int staffid,QList<unsigned int>& letterids);
    bool FetchReceivedLetters(const unsigned int staffid, QList<unsigned int> &letterids);
signals:
private:

    StaffInfoManager sim;
    LetterInfoManager lim;
    ReceiveInfoManager rim;
    SendInfoManager sendim;
};

#endif // LETTERSYSTEM_H
