#ifndef SERVER_H
#define SERVER_H

#include "../model/tetris.h"
#include "client.h"
#include <QtNetwork>

/*!
 * \brief Espace de nom de Guillaume Jouret & Guillaume Walravens.
 */
namespace GJ_GW{

class MultiTetris : public Tetris{
    Q_OBJECT
    QTcpServer *server_;
    QTcpSocket *socket_;
    Client client_;
    quint16 messageSize_;

public:
    explicit MultiTetris();
    QString getHostName() const;
    quint16 getPort() const;
    bool isListening() const;
    void closeServer(bool soloMode);
    void initClient(QString hostName, unsigned port);
    bool isClientConnected() const;
    void answerMessage(const QString &message);
    QString serverError() const;
    QString clientError() const;

private slots:
    void connection();
    void disconnection();
    void dataReception();
};

} // namespace GJ_GW

#endif // SERVER_H