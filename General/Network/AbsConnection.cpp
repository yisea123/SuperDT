#include "AbsConnection.h"
#include "clog.h"
#include <QtMath>

QString AbsConnection::getIpPort()
{
    return m_strIp + ":" + QString::number(m_nPort);
}

AbsConnection::~AbsConnection()
{
}

void AbsConnection::slotSend(QString strIpPort, QString strMessage)
{
    QString strMyIpPort = getIpPort();
    if(strMyIpPort.compare(strIpPort) != 0){
        return;
    }
    if( !m_bConnected ){
//        logWin()<<"AbsConnection::slotSend 没有有效连接:"<<strMyIpPort<<flushWin;
        return;
    }
    int nRes = -1;
    if(m_bIsWinProtocal){
        nRes = sendByWin(strMessage);
    }else{
        nRes = send(strMessage);
    }

    if (nRes == -1){
        logWarnningWin()<<"AbsConnection::slotSend 发送失败:"<<strMyIpPort<<flushWin;
    }
    else{
        //logWin()<<"AbsConnection::slotSend 发送成功:"<<strMyIpPort<<flushWin;
    }
}

void AbsConnection::slotSendByQByteArray(QString strIpPort, QByteArray arrMsg)
{
    // 这里进行 Win协议 的判断； 因为 Win协议 都是采用 String 字符串的， 发送请求数据同步信息会调用到这里
    if(m_bIsWinProtocal){
        QString strMessage(arrMsg);
        slotSend(strIpPort,strMessage);
    } else {
        QString strMyIpPort = getIpPort();
        if(strMyIpPort.compare(strIpPort) != 0){
            return;
        }


        if(nullptr == m_pTcpSocket){
            logErrorWin()<<"AbsConnection::send 逻辑错误，m_pTcpSocket为空"<<flushWin;
            return ;
        }

        m_pTcpSocket->write(arrMsg);
    }
}

void AbsConnection::slotDataReceived()
{
    if(m_bIsWinProtocal){
        dataReceviedByWin();
    }else{
        dataRecevied();
    }
}

int AbsConnection::send(QString strMessage)
{
    if(nullptr == m_pTcpSocket){
        logErrorWin()<<"AbsConnection::send 逻辑错误，m_pTcpSocket为空"<<flushWin;
        return -1;
    }
    return m_pTcpSocket->write(strMessage.toUtf8());
}

int AbsConnection::sendByWin(QString strMessage)
{
    if(nullptr == m_pTcpSocket){
        logErrorWin()<<"AbsConnection::sendByWin 逻辑错误，m_pTcpSocket为空"<<flushWin;
        return -1;
    }
    int nDataLength = strMessage.toUtf8().length();
    char* strSendMessage = new char[11+nDataLength];
    memcpy(strSendMessage, "WINCOMN", 7);
    memcpy(strSendMessage + 7, (char*)&nDataLength, sizeof(int));
    memcpy(strSendMessage + 11,strMessage.toStdString().c_str(),nDataLength);
    //注意！只有通过stdString及其长度发送，才能在服务端收到正确的utf-8编码的流
    return m_pTcpSocket->write(strSendMessage, 11+nDataLength);
}

void AbsConnection::dataRecevied()
{
    if(nullptr == m_pTcpSocket){
        logErrorWin()<<"AbsWinConnection::slotDataReceived 逻辑错误，m_pTcpSocket为空"<<flushWin;
        return;
    }
    while (1)//将数据读入缓存
    {
        int readCount = m_pTcpSocket->readLine(m_szBuffer,BUFFER_SIZE_CLIENTS);
        if (readCount <= 0){
            break;
        }
        QByteArray arrByte;
        arrByte.append(m_szBuffer,readCount);
        m_pNotifier->dataArrivedForInterface(arrByte,m_strIp, m_nPort);
        memset( m_szBuffer, 0, BUFFER_SIZE_CLIENTS );
    }
}

void AbsConnection::dataReceviedByWin()
{
    if(nullptr == m_pTcpSocket){
        logErrorWin()<<"AbsWinConnection::slotDataReceived 逻辑错误，m_pTcpSocket为空"<<flushWin;
        return;
    }
    while (1)//将数据读入缓存
    {
        int readCount = m_pTcpSocket->readLine(m_szBuffer,BUFFER_SIZE_CLIENTS);
        if (readCount <= 0){
            break;
        }
        QByteArray byteArr = splitPacket( m_totalByteArr, m_szBuffer,readCount);
        while ( !byteArr.isEmpty() )
        {
            m_pNotifier->dataArrivedForInterface(byteArr.data(),m_strIp, m_nPort);
            memset( m_szBuffer, 0, BUFFER_SIZE_CLIENTS );
            byteArr = splitPacket( m_totalByteArr, m_szBuffer,0);
        }
    }
}

/*
数据包格式如下：
    1.TCP传输的数据包：“包头”+“数据长度” +“数据”；
    2.包头：WINCOMN
    3.数据长度：int类型，大小为sizeof(int)
    4.数据：实际数据（例如json数据）
*/
QByteArray AbsConnection::splitPacket(QByteArray &oldPacket, char *newPacket, int nLength)
{
    QByteArray packet = oldPacket.append( newPacket, nLength);
    if(packet.length() <= 10)
        return QByteArray();
    char* packetData = packet.data();
    char cMark[7];
    memcpy(cMark, "WINCOMN", 7);
    int nIndex = 0;
    while(nIndex < packet.length())
    {
        char* pTemp = packetData + nIndex;
        if(!memcmp(cMark, pTemp, 7))
        {
            int nDataLen;
            memcpy( &nDataLen, pTemp +7, 4);
            int nHeadLen = sizeof(cMark) + sizeof(int);
            if ( packet.length() - nIndex >= (nHeadLen + nDataLen) )
            {
                QByteArray byteData;
                byteData.append( pTemp + nHeadLen, nDataLen );
                //如果数据大于有效数据，去除有效数据后将后面多余数据放入oldPacket，供下个包使用
                oldPacket.clear();
                if ( packet.length() - nIndex > nHeadLen + nDataLen )
                {
                    oldPacket.append( pTemp + nHeadLen + nDataLen, packet.length() - (nHeadLen + nDataLen + nIndex));
                }
                return byteData;
            }
        }
        nIndex++;
    }
    return QByteArray();
}

int AbsConnection::calculateLen(char *dataBuf)
{
    int len = 0;
    int bufLen = strlen( dataBuf );
    for ( int i = bufLen-1; i>=0; i-- )
    {
        len = len + (dataBuf[i]-'0') * (int)qPow( 10, bufLen-i-1 );
    }
    return len;
}
