#include "service.h"
#include "QSqlDatabase"
#include "QCoreApplication"
#include <QSqlQuery>
#include "user.h"
service* service::serv = new service();
service::service()
{
    /*
    QCoreApplication::addLibraryPath("")*/
    //    db = QSqlDatabase::addDatabase("QPSQL");
    //    db.setHostName("localhost");
    //    db.setPort(5432);
    //    db.setDatabaseName("idiot_no3");
    //    db.setUserName("postgres");
    //    db.setPassword("Lrz15562498929");
    db =QSqlDatabase::addDatabase("QPSQL");
    //连接数据库
    db.setPort(3308);
    db.setHostName("127.0.0.1"); //数据库服务器IP
    db.setUserName("postgres"); //数据库用户名
    db.setPassword("zxz123"); //数据库密码
    db.setDatabaseName("tickets"); //使用哪个数据库
    if( !db.open() ){ //数据库打开失败
        qDebug()<<"数据库连接出错";
    }
    else {
        qDebug("连接成功");
    }

}


service::~service() {
    delete serv;
}

service* service::getInstance() {
    return serv;
}

void service::handleRqst(QJsonObject& inJson, QJsonArray& outJsonArray) {
    //operation op = (operation)inJson.value("op").toInt();
    int res=inJson.value("request").toInt();
    QString temp=QString::number(res);
    qDebug()<<"request"<<temp;
    switch((operation)res){
    case DEBUG:
        qDebug("出错");
        debug(inJson,outJsonArray);
        break;
    case LOGIN:
        qDebug("request:login");
        login(inJson,outJsonArray);
        qDebug("request:login end");
        break;
    case REGISTER:
        qDebug("request:register");
        Register(inJson,outJsonArray);
        break;
    case DELETEPASSAGER:
        deletePassager(inJson,outJsonArray);
        break;
    case ADDPASSAGER:
        addPassager(inJson,outJsonArray);
        break;
    case SEARCHTICKETS:
        searchTickets(inJson,outJsonArray);
        break;
    case ORDER:
        createOrder(inJson,outJsonArray);
        break;
    case ORDERPASSAGER:
        addOrderPassager(inJson,outJsonArray);
        break;
    case UPDATEUSER:
        updateUser(inJson,outJsonArray);
        break;
    case SEARCHORDER:
        searchOrder(inJson,outJsonArray);
        break;
    case ORDERDETAIL:
        orderDetail(inJson,outJsonArray);
        break;
    case CANCELORDER:
        cancelOrder(inJson,outJsonArray);
        break;
    case SWITCHORDER:
        switchOrder(inJson,outJsonArray);
        break;
    case TRANSFER:
        transfer(inJson,outJsonArray);
        break;
    case PAYORDER:
        payOrder(inJson,outJsonArray);
    default:;
    }

}

void service::login(QJsonObject &dataIn,QJsonArray &dataOut){
    QString id=dataIn.value("uid").toString();
    QString psw=dataIn.value("psw").toString();
    //查询
    QString str=QString("select * from train_tickets.user_info where id = '%1'").arg(id);
    QSqlQuery query(db);
    query.exec(str);
    qDebug("查询中");//
    QString userName;
    QString userId;
    QString userPsw;
    double amount=0;
    QString phoneNumber;
    QString credentId;
    QString userSex;
    QString type;
    bool loginFlag;

    while(query.next()){
        userId=query.value(0).toString();
        userName=query.value(1).toString();
        userPsw=query.value(2).toString();
        amount=query.value(3).toDouble();
        phoneNumber=query.value(4).toString();
        credentId=query.value(5).toString();
        userSex=query.value(6).toString();
        type=query.value(7).toString();
        // passagerNum=query.value(8).toInt();
    }

    if(psw==userPsw){
        qDebug("登录成功");
        loginFlag=true;
        dataOut.append(loginFlag);
        dataOut.append(userId);
        dataOut.append(userPsw);
        dataOut.append(userName);
        dataOut.append(amount);
        dataOut.append(phoneNumber);
        dataOut.append(credentId);
        dataOut.append(userSex);
        dataOut.append(type);
    }else{
        loginFlag=false;
        dataOut.append(loginFlag);
        qDebug("登录失败");
    }

    //加载乘客
    QString str2=QString("select * from train_tickets.user_pass where id = '%1'").arg(id);
    QSqlQuery query2(db);
    query2.exec(str2);
    while (query2.next()) {
        QJsonObject passager;
        passager.insert("cId",query2.value(1).toString());
        passager.insert("name",query2.value(2).toString());
        passager.insert("phone",query2.value(3).toString());
        passager.insert("type",query2.value(4).toString());

        dataOut.append(passager);

    }
}

void service::Register(QJsonObject &dataIn, QJsonArray &dataOut)
{

    QString uid=dataIn.value("uid").toString();
    QString name=dataIn.value("name").toString();
    QString psw=dataIn.value("password").toString();
    QString phoneNumber=dataIn.value("phoneNumber").toString();
    double  amount =0;
    QString credentId=dataIn.value("credentId").toString();
    QString sex=dataIn.value("sex").toString();
    QString type=dataIn.value("type").toString();
    //        int passagerNum=dataIn.value("passagerNum").toInt();
    bool insertFlag=false;

    //插入
    QString str=QString("insert into train_tickets.user_info values(?,?,?,?,?,?,?,?)");
    QSqlQuery query(db);
    query.prepare(str);
    query.addBindValue(uid);
    query.addBindValue(name);
    query.addBindValue(psw);
    query.addBindValue(amount);
    query.addBindValue(phoneNumber);
    query.addBindValue(credentId);
    query.addBindValue(sex);
    query.addBindValue(type);
    //query.addBindValue(passagerNum);
    if(query.exec()){
        qDebug("request:login success");
        insertFlag=true;
        dataOut.append(insertFlag);
    }else {
        dataOut.append(insertFlag);
        qDebug("request:login 142");
    }

}

void service::deletePassager(QJsonObject &dataIn, QJsonArray &dataOut)
{
    QString uid=dataIn.value("userId").toString();
    QString cid=dataIn.value("cid").toString();

    QString str=QString("delete from train_tickets.user_pass where id = '%1'and pass_cid ='%2'").arg(uid).arg(cid);
    QSqlQuery query(db);
    query.prepare(str);
    if(query.exec()){
        qDebug("request:delete success");
        dataOut.append(true);
    }else{
        qDebug("request:delete fail");
        dataOut.append(false);
    }

}

void service::addPassager(QJsonObject &dataIn, QJsonArray &dataOut)
{
    QString uid=dataIn.value("uid").toString();
    QString name=dataIn.value("name").toString();
    QString phone=dataIn.value("phone").toString();
    QString cid=dataIn.value("cid").toString();
    QString type=dataIn.value("type").toString();

    QString str=QString("insert into train_tickets.user_pass values(?,?,?,?,?)");
    QSqlQuery query(db);
    query.prepare(str);
    query.addBindValue(uid);
    query.addBindValue(cid);
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(type);
    if(query.exec()){
        qDebug("request:add success");
        dataOut.append(true);
    }else{
        qDebug("request:add fail");
        dataOut.append(false);
    }


}

void service::searchTickets(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    //地点-》站名？？？

    QString fromStation=inJson.value("from").toString();
    QString toStation=inJson.value("to").toString();
    QString date=inJson.value("date").toString();

    QString from="%"+fromStation+"%";
    QString to="%"+toStation+"%";

    QString str=QString("select distinct (train_id) ,from_station,to_station,start_time,arrive_time,train_type,date from train_tickets.train natural join train_tickets.seat where from_station like ? and to_station like ?  and date=? order by start_time ");
    QSqlQuery query(db);
    query.prepare(str);
    query.addBindValue(from);
    query.addBindValue(to);
    query.addBindValue(date);

    if(query.exec()){
        qDebug("request:search success");
        outJsonArray.append(true);
        //查可用的车次
        while(query.next()){

            //查到一辆车 构建一个ticket
            QJsonObject ticket;
            ticket.insert("tId",query.value(0).toString());
            ticket.insert("from",query.value(1).toString());
            ticket.insert("to",query.value(2).toString());
            ticket.insert("startTime",query.value(3).toString());
            ticket.insert("arriveTime",query.value(4).toString());

            //得到该车的车次 始发站 终点站
            QString tid=query.value(0).toString();
            QString stationFrom=query.value(1).toString();
            QString stationTo=query.value(2).toString();

            //查该列车余票
            int ticketsNum0=0;
            int ticketsNum1=0;
            int ticketsNum2=0;

            QString strNum=QString("select * from train_tickets.train natural join train_tickets.seat where train_id=? and from_station=? and to_station=?  and date=? ");
            QSqlQuery queryNum(db);
            queryNum.prepare(strNum);
            queryNum.addBindValue(tid);
            queryNum.addBindValue(stationFrom);
            queryNum.addBindValue(stationTo);
            queryNum.addBindValue(date);

            if(queryNum.exec()){
                if(queryNum.first()){

                    //                      QString free=queryNum.value(9).toString();
                    // int  coach=query.value(6).toInt();

                    //计算余票
                    int order1;//出发站序号
                    int order2;//目的站序号

                    QString str2=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
                    QSqlQuery query2(db);
                    query2.prepare(str2);
                    query2.addBindValue(tid);
                    query2.addBindValue(stationFrom);
                    if(query2.exec()){
                        if(query2.first())
                            order1=query2.value(0).toInt();
                    }else{
                        qDebug("find order1 fail");
                        outJsonArray.replace(0,false);
                        return;
                    }

                    QString str3=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
                    QSqlQuery query3(db);
                    query3.prepare(str3);
                    query3.addBindValue(tid);
                    query3.addBindValue(stationTo);
                    if(query3.exec()){
                        if(query3.first())
                            order2=query3.value(0).toInt();
                    }else{
                        qDebug("find order2 fail");
                        outJsonArray.replace(0,false);
                        return;
                    }

                    int strNum=0;
                    QString freeArray;
                    QString str4=QString("select count(train_id) from train_tickets.pass_by where train_id=?");
                    QSqlQuery query4(db);

                    query4.prepare(str4);
                    query4.addBindValue(tid);

                    if(query4.exec()){
                        if(query4.first())
                            strNum=query4.value(0).toInt();

                        for(int i=0;i<strNum;i++){
                            if(i>=order1-1&&i<=order2-1){
                                freeArray+="1";
                            }else{
                                freeArray+="0";
                            }
                        }

                    }else{
                        qDebug("find strNum fail");
                        outJsonArray.replace(0,false);
                        return;
                    }

                    //获取商务余票
                    QString getNum0=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id= 1 and free=?|free");
                    QSqlQuery query5(db);
                    query5.prepare(getNum0);
                    query5.addBindValue(tid);
                    query5.addBindValue(date);
                    query5.addBindValue(freeArray);
                    if(query5.exec()){
                        if(query5.first())
                            ticketsNum0=query5.value(0).toInt();

                    }else{
                        qDebug("find num0 fail");
                        outJsonArray.replace(0,false);
                        return;
                    }

                    //获取一等座票
                    QString getNum1=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id>1 and coach_id<4 and free=?|free");
                    QSqlQuery query6(db);
                    query6.prepare(getNum1);
                    query6.addBindValue(tid);
                    query6.addBindValue(date);
                    query6.addBindValue(freeArray);
                    if(query6.exec()){
                        if(query6.first())
                            ticketsNum1=query6.value(0).toInt();

                    }else{
                        qDebug("find num1 fail");
                        outJsonArray.replace(0,false);
                        return;
                    }

                    //二等座
                    QString getNum2=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id>=4 and free=?|free");
                    QSqlQuery query7(db);
                    query7.prepare(getNum2);
                    query7.addBindValue(tid);
                    query7.addBindValue(date);
                    query7.addBindValue(freeArray);
                    if(query7.exec()){
                        if(query7.first())
                            ticketsNum2=query7.value(0).toInt();

                    }else{
                        qDebug("find num2 fail");
                        outJsonArray.replace(0,false);
                        return;
                    }

                    ticket.insert("ticketsNum0",ticketsNum0);
                    ticket.insert("ticketsNum1",ticketsNum1);
                    ticket.insert("ticketsNum2",ticketsNum2);


                }else{
                    qDebug("request:find num fail");
                    outJsonArray.replace(0,false);
                    return;
                }
                outJsonArray.append(ticket);
            }
        }
    }else{
        qDebug("request:search fail");
        outJsonArray.replace(0,false);

    }

}

void service::createOrder(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    QString uid=inJson.value("uid").toString();
    QString time=inJson.value("time").toString();
    double sum=inJson.value("price").toDouble();
    QString status="未支付";
    QString inoutNo;
    inoutNo = QString("P"+QDate::currentDate().toString("yyyyMMdd"));
    QSqlQuery queryCount(db);
    int count =1;
    queryCount.prepare("select count(order_id) from train_tickets.order_info where order_date like ?");
    QString str1=QString(QDate::currentDate().toString("yyyy-MM-dd"))+"%";
    queryCount.addBindValue(str1);
    queryCount.exec();
    if(queryCount.next()){
        count=queryCount.value(0).toInt()+1;
    }
    QString temp=QString("0000%1").arg(count);
    temp=temp.right(4);
    inoutNo+=temp;

    QSqlQuery query(db);
    QString str=QString("insert into train_tickets.order_info values(?,?,?,?,?)");
    query.prepare(str);
    query.addBindValue(inoutNo);
    query.addBindValue(uid);
    query.addBindValue(time);
    query.addBindValue(status);
    query.addBindValue(sum);
    if(query.exec()){
        outJsonArray.append(true);
        outJsonArray.append(inoutNo);
    }else{
        outJsonArray.append(false);
    }
}

void service::addOrderPassager(QJsonObject &inJson, QJsonArray &outJsonArray)
{

    QString orderId=inJson.value("orderId").toString();
    QString trainId=inJson.value("trainId").toString();
    QString fromStation=inJson.value("fromStation").toString();
    QString toStation=inJson.value("toStation").toString();
    QString date=inJson.value("date").toString();
    QJsonArray info=inJson.value("info").toArray();

    int num0=inJson.value("num0").toInt();//二等座数
    int num1=inJson.value("num1").toInt();
    int num2=inJson.value("num2").toInt();

    int *mark2;//二等座
    int *mark1;
    int *mark0;

    int tag2=0;
    int tag1=0;
    int tag0=0;

    if(num0>=1){
        mark2=new int[num0];
    }

    if(num1>=1){
        mark1=new int[num1];
    }

    if(num2>=1){
        mark0=new int[num2];
    }

    for(int i=2;i<info.size();i=i+5){
        if(info.at(i).toString()=="二等座"){
            mark2[tag2]=i-2;
            tag2++;
        }
        if(info.at(i).toString()=="一等座"){
            mark1[tag1]=i-2;
            tag1++;
        }
        if(info.at(i).toString()=="商务座"){
            mark0[tag0]=i-2;
            tag0++;
        }
    }

    //制作bit
    int order1;//出发站序号
    int order2;//目的站序号

    QString str2=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
    QSqlQuery query2(db);
    query2.prepare(str2);
    query2.addBindValue(trainId);
    query2.addBindValue(fromStation);
    if(query2.exec()){
        if(query2.first())
            order1=query2.value(0).toInt();
    }else{
        qDebug("find order1 fail");
        outJsonArray.replace(0,false);
        return;
    }

    QString str3=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
    QSqlQuery query3(db);
    query3.prepare(str3);
    query3.addBindValue(trainId);
    query3.addBindValue(toStation);
    if(query3.exec()){
        if(query3.first())
            order2=query3.value(0).toInt();
    }else{
        qDebug("find order2 fail");
        outJsonArray.replace(0,false);
        return;
    }

    int strNum=0;
    QString freeArray,usedFree;//检测比特串  和购买后的比特串片段
    QString str4=QString("select count(train_id) from train_tickets.pass_by where train_id=?");
    QSqlQuery query4(db);
    query4.prepare(str4);
    query4.addBindValue(trainId);

    if(query4.exec()){
        if(query4.first())
            strNum=query4.value(0).toInt();

        for(int i=0;i<strNum;i++){
            if(i>=order1-1&&i<=order2-1){
                freeArray+="1";
                usedFree+="0";
            }else{
                freeArray+="0";
            }
        }

    }else{
        qDebug("find strNum fail");
        outJsonArray.replace(0,false);
        return;
    }
    qDebug()<<"order 2";
    if(num0>0){//处理二等座乘客
        QSqlQuery query(db);
        QString str=QString("select * from train_tickets.seat where train_id=? and date=? and coach_id>=4 and free=?|free order by coach_id");
        query.prepare(str);
        query.addBindValue(trainId);
        query.addBindValue(date);
        query.addBindValue(freeArray);
        if(query.exec()){
        int count=0;
        while(query.next()){
            if(count>=num0) break;//

            int coach=query.value(1).toInt();
            QString seat=query.value(2).toString();
            QString tempFree=query.value(4).toString();
            QString newFree=tempFree.mid(0,order1-1)+usedFree+tempFree.mid(order2);
            QSqlQuery queryBuy(db);
            queryBuy.prepare("update train_tickets.seat set free =? where train_id =? and coach_id=? and seat_id=? and date=?");//更改座位
            queryBuy.addBindValue(newFree);
            queryBuy.addBindValue(trainId);
            queryBuy.addBindValue(coach);
            queryBuy.addBindValue(seat);
            queryBuy.addBindValue(date);
            if(queryBuy.exec()){
                QString name;
                QString cid;
                QString type;
                double price;
                //提取乘客信息并插入数据库  第count位乘客
                 name=info.at(mark2[count]).toString();
                 cid=info.at(mark2[count]+1).toString();
                 type=info.at(mark2[count]+3).toString();
                 price=info.at(mark2[count]+4).toDouble();

                QSqlQuery queryOrder(db);
                queryOrder.prepare("insert into train_tickets.order_pass values(?,?,?,?,?,?,?,?,?,?,?,?)");
                queryOrder.addBindValue(orderId);
                queryOrder.addBindValue(trainId);
                queryOrder.addBindValue(cid);
                queryOrder.addBindValue(name);
                queryOrder.addBindValue(fromStation);
                queryOrder.addBindValue(toStation);
                queryOrder.addBindValue(coach);
                queryOrder.addBindValue(type);
                queryOrder.addBindValue(seat);
                queryOrder.addBindValue(price);
                queryOrder.addBindValue("未支付");
                queryOrder.addBindValue(date);

                if(queryOrder.exec()){
                    count++;
                }else{
                    qDebug()<<"insert order fail";
                    outJsonArray.append(false);
                    return;
                }
            }

        }
      }else{
            qDebug()<<"search seat fail";
            outJsonArray.append(false);
            return;
        }
    }
        qDebug()<<"order 1";
    if(num1>0){//处理一等座乘客
        QSqlQuery query(db);
        QString str=QString("select * from train_tickets.seat where train_id=? and date=? and coach_id>1 and coach_id<4 and free=?|free order by coach_id");
        query.prepare(str);
        query.addBindValue(trainId);
        query.addBindValue(date);
        query.addBindValue(freeArray);
        if(query.exec()){
        int count=0;
        while(query.next()){
            if(count>=num1) break;//
            int coach=query.value(1).toInt();
            QString seat=query.value(2).toString();
            QString tempFree=query.value(4).toString();
            QString newFree=tempFree.mid(0,order1-1)+usedFree+tempFree.mid(order2);
            QSqlQuery queryBuy(db);
            queryBuy.prepare("update train_tickets.seat set free =? where train_id =? and coach_id=? and seat_id=? and date=?");
            queryBuy.addBindValue(newFree);
            queryBuy.addBindValue(trainId);
            queryBuy.addBindValue(coach);
            queryBuy.addBindValue(seat);
            queryBuy.addBindValue(date);
            if(queryBuy.exec()){
                QString name;
                QString cid;
                QString type;
                double price;
                //提取乘客信息并插入数据库  第count位乘客
                name=info.at(mark1[count]).toString();
                cid=info.at(mark1[count]+1).toString();
                type=info.at(mark1[count]+3).toString();
                price=info.at(mark1[count]+4).toDouble();

                QSqlQuery queryOrder(db);
                queryOrder.prepare("insert into train_tickets.order_pass values(?,?,?,?,?,?,?,?,?,?,?,?)");
                queryOrder.addBindValue(orderId);
                queryOrder.addBindValue(trainId);
                queryOrder.addBindValue(cid);
                queryOrder.addBindValue(name);
                queryOrder.addBindValue(fromStation);
                queryOrder.addBindValue(toStation);
                queryOrder.addBindValue(coach);
                queryOrder.addBindValue(type);
                queryOrder.addBindValue(seat);
                queryOrder.addBindValue(price);
                queryOrder.addBindValue("未支付");
                queryOrder.addBindValue(date);

                if(queryOrder.exec()){
                    count++;
                }else{
                    qDebug()<<"insert order fail";
                    outJsonArray.append(false);
                    return;
                }
            }

        }
      }else{
            qDebug()<<"search seat fail";
            outJsonArray.append(false);
            return;
        }
    }
qDebug()<<"order 0";
    if(num2>0){//处理商务座乘客
        QSqlQuery query(db);
        QString str=QString("select * from train_tickets.seat where train_id=? and date=? and coach_id=1 and free=?|free order by seat_id");
        query.prepare(str);
        query.addBindValue(trainId);
        query.addBindValue(date);
        query.addBindValue(freeArray);
        if(query.exec()){
        int count=0;
        while(query.next()){
            if(count>=num2) break;//
            int coach=query.value(1).toInt();
            QString seat=query.value(2).toString();
            QString tempFree=query.value(4).toString();
            QString newFree=tempFree.mid(0,order1-1)+usedFree+tempFree.mid(order2);
            QSqlQuery queryBuy(db);
            queryBuy.prepare("update train_tickets.seat set free =? where train_id =? and coach_id=? and seat_id=? and date=?");
            queryBuy.addBindValue(newFree);
            queryBuy.addBindValue(trainId);
            queryBuy.addBindValue(coach);
            queryBuy.addBindValue(seat);
            queryBuy.addBindValue(date);
            if(queryBuy.exec()){
                QString name;
                QString cid;
                QString type;
                double price;
                //提取乘客信息并插入数据库  第count位乘客
                name=info.at(mark0[count]).toString();
                cid=info.at(mark0[count]+1).toString();
                type=info.at(mark0[count]+3).toString();
                price=info.at(mark0[count]+4).toDouble();

                QSqlQuery queryOrder(db);
                queryOrder.prepare("insert into train_tickets.order_pass values(?,?,?,?,?,?,?,?,?,?,?,?)");
                queryOrder.addBindValue(orderId);
                queryOrder.addBindValue(trainId);
                queryOrder.addBindValue(cid);
                queryOrder.addBindValue(name);
                queryOrder.addBindValue(fromStation);
                queryOrder.addBindValue(toStation);
                queryOrder.addBindValue(coach);
                queryOrder.addBindValue(type);
                queryOrder.addBindValue(seat);
                queryOrder.addBindValue(price);
                queryOrder.addBindValue("未支付");
                queryOrder.addBindValue(date);
                if(queryOrder.exec()){
                    count++;
                }else{
                    qDebug()<<"insert order fail";
                    outJsonArray.append(false);
                    return;
                }
            }

        }
      }else{
            qDebug()<<"search seat fail";
            outJsonArray.append(false);
        }
    }
    //更新总价
    QSqlQuery queryPrice(db);
    queryPrice.prepare("update train_tickets.order_info set total_price=(select sum(price) from train_tickets.order_pass where order_id=?) where order_id=? ");
    queryPrice.addBindValue(orderId);
    queryPrice.addBindValue(orderId);
    queryPrice.exec();

    qDebug()<<"order success";
    outJsonArray.append(true);
}

void service::updateUser(QJsonObject &dataIn, QJsonArray &dataOut)
{
    QString id=dataIn.value("uid").toString();
//    QString psw=dataIn.value("psw").toString();

    //加载乘客
    QString str2=QString("select * from train_tickets.user_pass where id = '%1'").arg(id);
    QSqlQuery query2(db);
    query2.exec(str2);
    while (query2.next()) {
        QJsonObject passager;
        passager.insert("cId",query2.value(1).toString());
        passager.insert("name",query2.value(2).toString());
        passager.insert("phone",query2.value(3).toString());
        passager.insert("type",query2.value(4).toString());

        dataOut.append(passager);
    }
}

void service::searchOrder(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    QString uid=inJson.value("uid").toString();
    QSqlQuery query(db);
    QString str=QString("select * from train_tickets.order_info  where user_id = ? order by order_date desc");
    query.prepare(str);
    query.addBindValue(uid);
    if(query.exec()){
        while(query.next()){//一堆订单中的一张 循环遍历
            QString orderId=query.value(0).toString();
            QString orderDate=query.value(2).toString().mid(0,19);
            QString status=query.value(3).toString();
            double totalPrice=query.value(4).toDouble();
//            QString str1=QString("select train_id,from_station,to_station,start_time,arrive_time,date from train_tickets.order_pass natural join train_tickets.train  where order_id = ?");
//            QSqlQuery query1(db);  //更多信息
//            query1.prepare(str1);
//            query1.addBindValue(orderId);

//            QString trainId;
//            QString fromStation;
//            QString toStation;
//            QString startTime;
//            QString arriveTime;
//            QString date;

//            if(query1.exec()){
//                if(query1.first()){
//                    trainId=query1.value(0).toString();
//                    fromStation=query1.value(1).toString();
//                    toStation=query1.value(2).toString();
//                    startTime=query1.value(3).toString();
//                    arriveTime=query1.value(4).toString();
//                    QString dateTemp=query1.value(5).toString();
//                    date=dateTemp.mid(0,10);
//                }
                QJsonObject tempOrder;
                tempOrder.insert("orderId",orderId);
//                tempOrder.insert("trainId",trainId);
//                tempOrder.insert("fromStation",fromStation);
//                tempOrder.insert("toStation",toStation);
//                tempOrder.insert("startTime",startTime);
//                tempOrder.insert("arriveTime",arriveTime);
//                tempOrder.insert("date",date);
                tempOrder.insert("status",status);
                tempOrder.insert("price",totalPrice);
                tempOrder.insert("orderDate",orderDate);

                outJsonArray.append(tempOrder);
//            }else{
//                qDebug()<<"order fail";
//            }
        }
    }else{
         qDebug()<<"order fail2";
    }
}

void service::orderDetail(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    QString orderId=inJson.value("orderId").toString();
    QSqlQuery query(db);
    query.prepare("select cid,name,coach,passager_type,seat_id,price,ticket_status,date,train_tickets.train.train_id,train_tickets.order_pass.from_station,train_tickets.order_pass.to_station,start_time,arrive_time,train_type from train_tickets.order_pass  join train_tickets.train on train_tickets.train.train_id = train_tickets.order_pass.train_id  where order_id =? order by cid");
    query.addBindValue(orderId);
    if(query.exec()){
        while(query.next()){
            QString cid=query.value(0).toString();
            QString name=query.value(1).toString();
            int coach=query.value(2).toInt();
            QString passagerType=query.value(3).toString();
            QString seat=query.value(4).toString();
            double price=query.value(5).toDouble();
            QString ticketStatus=query.value(6).toString();
            QString ticketDate=query.value(7).toString();
            QString trainId=query.value(8).toString();
            QString fromStation=query.value(9).toString();
            QString toStation=query.value(10).toString();
            QString startTime=query.value(11).toString();
            QString arriveTime=query.value(12).toString();
            QString trainType=query.value(13).toString();


            QJsonObject temp;
            temp.insert("cid",cid);
            temp.insert("name",name);
            temp.insert("coach",coach);
            temp.insert("passagerType",passagerType);
            temp.insert("seat",seat);
            temp.insert("price",price);
            temp.insert("ticketStatus",ticketStatus);
            temp.insert("trainId",trainId);
            temp.insert("fromStation",fromStation);
            temp.insert("toStation",toStation);
            temp.insert("startTime",startTime);
            temp.insert("arriveTime",arriveTime);
            temp.insert("ticketDate",ticketDate);
            temp.insert("trainType",trainType);
            outJsonArray.append(temp);
        }
        qDebug()<<"orderDetail success";
    }else{
        outJsonArray.append(false);
        qDebug()<<"orderDetail fail";
    }
}

void service::cancelOrder(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    QString orderId=inJson.value("orderId").toString();
    QString cid=inJson.value("cid").toString();
    QString date=inJson.value("ticketDate").toString();
    QString trainId=inJson.value("trainId").toString();
    QString fromStation=inJson.value("fromStation").toString();
    QString toStation=inJson.value("toStation").toString();
    int coach=inJson.value("coach").toInt();
    QString seat=inJson.value("seat").toString();
    QSqlQuery query(db);
    if(inJson.value("flag").toInt()==0){
    query.prepare("update train_tickets.order_pass set ticket_status ='已退票' where order_id=? and cid=? and train_id=? ");
    }else{
    query.prepare("update train_tickets.order_pass set ticket_status ='已改签' where order_id=? and cid=? and train_id=?");
    }
    query.addBindValue(orderId);
    query.addBindValue(cid);
    query.addBindValue(trainId);
    if(query.exec()){

        //制作比特串
        int order1;//出发站序号
        int order2;//目的站序号

        QString str2=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
        QSqlQuery query2(db);
        query2.prepare(str2);
        query2.addBindValue(trainId);
        query2.addBindValue(fromStation);
        if(query2.exec()){
            if(query2.first())
                order1=query2.value(0).toInt();
        }else{
            qDebug("find order1 fail");
            outJsonArray.replace(0,false);
            return;
        }

        QString str3=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
        QSqlQuery query3(db);
        query3.prepare(str3);
        query3.addBindValue(trainId);
        query3.addBindValue(toStation);
        if(query3.exec()){
            if(query3.first())
                order2=query3.value(0).toInt();
        }else{
            qDebug("find order2 fail");
            outJsonArray.replace(0,false);
            return;
        }

        int strNum=0;
        QString freeArray;
        QString str4=QString("select count(train_id) from train_tickets.pass_by where train_id=?");
        QSqlQuery query4(db);

        query4.prepare(str4);
        query4.addBindValue(trainId);

        if(query4.exec()){
            if(query4.first())
                strNum=query4.value(0).toInt();

            for(int i=0;i<strNum;i++){
                if(i>=order1-1&&i<=order2-1){
                    freeArray+="1";
                }else{
                    freeArray+="0";
                }
            }

        }else{
            qDebug("find strNum fail");
            outJsonArray.append(false);
            return;
        }

        //
        QSqlQuery query1(db);
        query1.prepare("update train_tickets.seat set free =?|free where train_id=? and coach_id=? and seat_id=? and date=? ");
        query1.addBindValue(freeArray);
        query1.addBindValue(trainId);
        query1.addBindValue(coach);
        query1.addBindValue(seat);
        query1.addBindValue(date);
        if(query1.exec()){
            QSqlQuery queryOrder(db);
            queryOrder.prepare("select count(order_id) from train_tickets.order_pass where order_id =? and ticket_status !='已退票' ");
            queryOrder.addBindValue(orderId);
            if(queryOrder.exec()){
                if(queryOrder.first()){
                    if(queryOrder.value(0).toInt()==0){//如果全部退票
                        QSqlQuery updateOrder(db);
                        updateOrder.prepare("update train_tickets.order_info set order_status ='已失效' where order_id =?");
                        updateOrder.addBindValue(orderId);
                        if(updateOrder.exec()){
                            qDebug()<<" all cancel update order success";
                        }
                        else{
                            qDebug()<<" all cancel but update order fail";
                        }
                    }
                }
            }
            outJsonArray.append(true);
            qDebug()<<"update seat success";
        }else{
            qDebug()<<"update seat fail";
            outJsonArray.append(false);
            return;
        }
    }else{
        qDebug()<<"cancel order fail";
        outJsonArray.append(false);
        return;
    }

}

//改签
void service::switchOrder(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    //更改order_pass 和seat的状态
    QString orderId=inJson.value("orderId").toString();
    QString oldTrainId=inJson.value("trainId").toString();
    QJsonArray info=inJson.value("ticketInfo").toArray();

    QString trainId=info.at(0).toString();
    QString fromStation=info.at(1).toString();
    QString toStation=info.at(2).toString();
    QString date=info.at(3).toString();
    QString passagerType=info.at(4).toString();
    QString chairType=info.at(5).toString();
    double price=info.at(6).toDouble();

    QString name=inJson.value("name").toString();
    QString cid=inJson.value("cid").toString();




    //制作bit
    int order1;//出发站序号
    int order2;//目的站序号

    QString str2=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
    QSqlQuery query2(db);
    query2.prepare(str2);
    query2.addBindValue(trainId);
    query2.addBindValue(fromStation);
    if(query2.exec()){
        if(query2.first())
            order1=query2.value(0).toInt();
    }else{
        qDebug("find order1 fail");
        outJsonArray.replace(0,false);
        return;
    }

    QString str3=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
    QSqlQuery query3(db);
    query3.prepare(str3);
    query3.addBindValue(trainId);
    query3.addBindValue(toStation);
    if(query3.exec()){
        if(query3.first())
            order2=query3.value(0).toInt();
    }else{
        qDebug("find order2 fail");
        outJsonArray.replace(0,false);
        return;
    }

    int strNum=0;
    QString freeArray,usedFree;//检测比特串  和购买后的比特串片段
    QString str4=QString("select count(train_id) from train_tickets.pass_by where train_id=?");
    QSqlQuery query4(db);
    query4.prepare(str4);
    query4.addBindValue(trainId);

    if(query4.exec()){
        if(query4.first())
            strNum=query4.value(0).toInt();

        for(int i=0;i<strNum;i++){
            if(i>=order1-1&&i<=order2-1){
                freeArray+="1";
                usedFree+="0";
            }else{
                freeArray+="0";
            }
        }

    }else{
        qDebug("find strNum fail");
        outJsonArray.replace(0,false);
        return;
    }
    qDebug()<<"order 2";

        QSqlQuery query(db);
        QString str;
        if(chairType=="二等座"){
         str=QString("select * from train_tickets.seat where train_id=? and date=? and coach_id>=4 and free=?|free order by coach_id");
        }else if(chairType=="一等座"){
         str=QString("select * from train_tickets.seat where train_id=? and date=? and coach_id>1 and coach_id<4 and free=?|free order by coach_id");
        }else {
         str=QString("select * from train_tickets.seat where train_id=? and date=? and coach_id=1 and free=?|free order by coach_id");
        }
        query.prepare(str);
        query.addBindValue(trainId);
        query.addBindValue(date);
        query.addBindValue(freeArray);
        if(query.exec()){
        if(query.first()){
            int coach=query.value(1).toInt();
            QString seat=query.value(2).toString();
            QString tempFree=query.value(4).toString();
            QString newFree=tempFree.mid(0,order1-1)+usedFree+tempFree.mid(order2);
            QSqlQuery queryBuy(db);
            queryBuy.prepare("update train_tickets.seat set free =? where train_id =? and coach_id=? and seat_id=? and date=?");//更改座位free
            queryBuy.addBindValue(newFree);
            queryBuy.addBindValue(trainId);
            queryBuy.addBindValue(coach);
            queryBuy.addBindValue(seat);
            queryBuy.addBindValue(date);
            if(queryBuy.exec()){

                //更新order——pass

                QSqlQuery queryOrder(db);
                queryOrder.prepare("update train_tickets.order_pass set train_id=?,from_station=?,to_station=?,coach=?,passager_type=?,seat_id=?,price=?,date=? where order_id=? and cid=? and train_id=?");//??????

                queryOrder.addBindValue(trainId);
                queryOrder.addBindValue(fromStation);
                queryOrder.addBindValue(toStation);
                queryOrder.addBindValue(coach);
                queryOrder.addBindValue(passagerType);
                queryOrder.addBindValue(seat);
                queryOrder.addBindValue(price);
                queryOrder.addBindValue(date);
                queryOrder.addBindValue(orderId);
                queryOrder.addBindValue(cid);
                queryOrder.addBindValue(oldTrainId);


                if(queryOrder.exec()){
                    //更新 order_info total_price
                     QSqlQuery queryPrice(db);
                     queryPrice.prepare("update train_tickets.order_info set total_price=(select sum(price) from train_tickets.order_pass where order_id=?) where order_id=? ");
                     queryPrice.addBindValue(orderId);
                     queryPrice.addBindValue(orderId);
                     queryPrice.exec();
                    outJsonArray.append(true);

                }else{
                    qDebug()<<"update order_pass fail";
                    outJsonArray.append(false);
                    return;
                }
            }
        }
      }else{
            qDebug()<<"search seat fail";
            outJsonArray.append(false);
            return;
        }



}

void service::transfer(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    QString fromStation=inJson.value("from").toString();
    QString toStation=inJson.value("to").toString();
    QString date=inJson.value("date").toString();

    QString from="%"+fromStation+"%";
    QString to="%"+toStation+"%";

    QSqlQuery query(db);
    QString str=QString("select * from(select pa.train_id as first_train_id, pa.station_id as first_departure_station, pa.start_time as first_start_time, pb.station_id as first_arrival_station, pb.arrival_time as first_arrival_time, pb.city as first_arrival_city from (train_tickets.pass_by natural join train_tickets.station)as pa join (train_tickets.pass_by natural join train_tickets.station) as pb on pa.train_id = pb.train_id where pa.arrival_order < pb.arrival_order and pa.city =? )as ta join (select pc.train_id as second_train_id, pc.station_id as second_departure_station, pc.start_time as second_start_time, pd.station_id as second_arrival_station, pd.arrival_time as second_arrival_time, pc.city as second_start_city, pd.day as arrival_day from (train_tickets.pass_by natural join train_tickets.station) as pc join (train_tickets.pass_by natural join train_tickets.station) as pd on pc.train_id = pd.train_id where pc.arrival_order < pd.arrival_order and pd.station_id like ? )as tb on ta.first_arrival_city = tb.second_start_city where ta.first_arrival_time < tb.second_start_time or (ta.first_arrival_time > tb.second_start_time and tb.arrival_day > 0) order by first_start_time");
    query.prepare(str);
    query.addBindValue(fromStation);
    query.addBindValue(to);
    if(query.exec()){
        int queryitNum=0;
    while (query.next()) {
        queryitNum++;
        if(queryitNum>8)break;
        QString firstTid=query.value(0).toString();
        QString firstFrom=query.value(1).toString();
        QString firstStartTime=query.value(2).toString();
        QString firstTo=query.value(3).toString();
        QString firstToTime=query.value(4).toString();
        QString secondTid=query.value(6).toString();
        QString secondFrom=query.value(7).toString();
        QString secondStartTime=query.value(8).toString();
        QString secondTo=query.value(9).toString();
        QString secondToTime=query.value(10).toString();

            // 构建一第一个ticket
        if(true){
            QJsonObject ticket;
            ticket.insert("tId",firstTid);
            ticket.insert("from",firstFrom);
            ticket.insert("to",firstTo);
            ticket.insert("startTime",firstStartTime);
            ticket.insert("arriveTime",firstToTime);

            //查该列车余票
            int ticketsNum0=0;
            int ticketsNum1=0;
            int ticketsNum2=0;

//            QString strNum=QString("select * from train_tickets.train natural join train_tickets.seat where train_id=? and from_station=? and to_station=?  and date=? ");
//            QSqlQuery queryNum(db);
//            queryNum.prepare(strNum);
//            queryNum.addBindValue(firstTid);
//            queryNum.addBindValue(firstFrom);
//            queryNum.addBindValue(firstTo);
//            queryNum.addBindValue(date);

//            if(queryNum.exec()){
//                if(queryNum.first()){

                    //计算余票
                    int order1;//出发站序号
                    int order2;//目的站序号

                    QString str2=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
                    QSqlQuery query2(db);
                    query2.prepare(str2);
                    query2.addBindValue(firstTid);
                    query2.addBindValue(firstFrom);
                    if(query2.exec()){
                        if(query2.first())
                            order1=query2.value(0).toInt();
                    }else{
                        qDebug("find order1 fail");

                        return;
                    }

                    QString str3=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
                    QSqlQuery query3(db);
                    query3.prepare(str3);
                    query3.addBindValue(firstTid);
                    query3.addBindValue(firstTo);
                    if(query3.exec()){
                        if(query3.first())
                            order2=query3.value(0).toInt();
                    }else{
                        qDebug("find order2 fail");

                        return;
                    }

                    int strNum=0;
                    QString freeArray;
                    QString str4=QString("select count(train_id) from train_tickets.pass_by where train_id=?");
                    QSqlQuery query4(db);

                    query4.prepare(str4);
                    query4.addBindValue(firstTid);

                    if(query4.exec()){
                        if(query4.first())
                            strNum=query4.value(0).toInt();

                        for(int i=0;i<strNum;i++){
                            if(i>=order1-1&&i<=order2-1){
                                freeArray+="1";
                            }else{
                                freeArray+="0";
                            }
                        }

                    }else{
                        qDebug("find strNum fail");

                        return;
                    }

                    //获取商务余票
                    QString getNum0=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id= 1 and free=?|free");
                    QSqlQuery query5(db);
                    query5.prepare(getNum0);
                    query5.addBindValue(firstTid);
                    query5.addBindValue(date);
                    query5.addBindValue(freeArray);
                    if(query5.exec()){
                        if(query5.first())
                            ticketsNum0=query5.value(0).toInt();

                    }else{
                        qDebug("find num0 fail");

                        return;
                    }

                    //获取一等座票
                    QString getNum1=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id>1 and coach_id<4 and free=?|free");
                    QSqlQuery query6(db);
                    query6.prepare(getNum1);
                    query6.addBindValue(firstTid);
                    query6.addBindValue(date);
                    query6.addBindValue(freeArray);
                    if(query6.exec()){
                        if(query6.first())
                            ticketsNum1=query6.value(0).toInt();

                    }else{
                        qDebug("find num1 fail");

                        return;
                    }

                    //二等座
                    QString getNum2=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id>=4 and free=?|free");
                    QSqlQuery query7(db);
                    query7.prepare(getNum2);
                    query7.addBindValue(firstTid);
                    query7.addBindValue(date);
                    query7.addBindValue(freeArray);
                    if(query7.exec()){
                        if(query7.first())
                            ticketsNum2=query7.value(0).toInt();

                    }else{
                        qDebug("find num2 fail");

                        return;
                    }

                    ticket.insert("ticketsNum0",ticketsNum0);
                    ticket.insert("ticketsNum1",ticketsNum1);
                    ticket.insert("ticketsNum2",ticketsNum2);


//                }else{
//                    qDebug("request:find num fail");

//                    return;
//                }
                outJsonArray.append(ticket);
            }



        //构建第二个ticket
        if(true){
            QJsonObject ticket;
            ticket.insert("tId",secondTid);
            ticket.insert("from",secondFrom);
            ticket.insert("to",secondTo);
            ticket.insert("startTime",secondStartTime);
            ticket.insert("arriveTime",secondToTime);

            //查该列车余票
            int ticketsNum0=0;
            int ticketsNum1=0;
            int ticketsNum2=0;

//            QString strNum=QString("select * from train_tickets.train natural join train_tickets.seat where train_id=? and from_station=? and to_station=?  and date=? ");
//            QSqlQuery queryNum(db);
//            queryNum.prepare(strNum);
//            queryNum.addBindValue(secondTid);
//            queryNum.addBindValue(secondFrom);
//            queryNum.addBindValue(secondTo);
//            queryNum.addBindValue(date);

//            if(queryNum.exec()){
//                if(queryNum.first()){

                    //                      QString free=queryNum.value(9).toString();
                    // int  coach=query.value(6).toInt();

                    //计算余票
                    int order1;//出发站序号
                    int order2;//目的站序号

                    QString str2=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
                    QSqlQuery query2(db);
                    query2.prepare(str2);
                    query2.addBindValue(secondTid);
                    query2.addBindValue(secondFrom);
                    if(query2.exec()){
                        if(query2.first())
                            order1=query2.value(0).toInt();
                    }else{
                        qDebug("find order1 fail");

                        return;
                    }

                    QString str3=QString("select arrival_order from train_tickets.pass_by where train_id=? and station_id=?");
                    QSqlQuery query3(db);
                    query3.prepare(str3);
                    query3.addBindValue(secondTid);
                    query3.addBindValue(secondTo);
                    if(query3.exec()){
                        if(query3.first())
                            order2=query3.value(0).toInt();
                    }else{
                        qDebug("find order2 fail");

                        return;
                    }

                    int strNum=0;
                    QString freeArray;
                    QString str4=QString("select count(train_id) from train_tickets.pass_by where train_id=?");
                    QSqlQuery query4(db);

                    query4.prepare(str4);
                    query4.addBindValue(secondTid);

                    if(query4.exec()){
                        if(query4.first())
                            strNum=query4.value(0).toInt();

                        for(int i=0;i<strNum;i++){
                            if(i>=order1-1&&i<=order2-1){
                                freeArray+="1";
                            }else{
                                freeArray+="0";
                            }
                        }

                    }else{
                        qDebug("find strNum fail");
                        outJsonArray.replace(0,false);
                        return;
                    }

                    //获取商务余票
                    QString getNum0=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id= 1 and free=?|free");
                    QSqlQuery query5(db);
                    query5.prepare(getNum0);
                    query5.addBindValue(secondTid);
                    query5.addBindValue(date);
                    query5.addBindValue(freeArray);
                    if(query5.exec()){
                        if(query5.first())
                            ticketsNum0=query5.value(0).toInt();

                    }else{
                        qDebug("find num0 fail");

                        return;
                    }

                    //获取一等座票
                    QString getNum1=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id>1 and coach_id<4 and free=?|free");
                    QSqlQuery query6(db);
                    query6.prepare(getNum1);
                    query6.addBindValue(secondTid);
                    query6.addBindValue(date);
                    query6.addBindValue(freeArray);
                    if(query6.exec()){
                        if(query6.first())
                            ticketsNum1=query6.value(0).toInt();

                    }else{
                        qDebug("find num1 fail");

                        return;
                    }

                    //二等座
                    QString getNum2=QString("select count (free) from train_tickets.seat where train_id=? and date =? and coach_id>=4 and free=?|free");
                    QSqlQuery query7(db);
                    query7.prepare(getNum2);
                    query7.addBindValue(secondTid);
                    query7.addBindValue(date);
                    query7.addBindValue(freeArray);
                    if(query7.exec()){
                        if(query7.first())
                            ticketsNum2=query7.value(0).toInt();

                    }else{
                        qDebug("find num2 fail");

                        return;
                    }

                    ticket.insert("ticketsNum0",ticketsNum0);
                    ticket.insert("ticketsNum1",ticketsNum1);
                    ticket.insert("ticketsNum2",ticketsNum2);


//                }else{
//                    qDebug("request:find num fail");

//                    return;
//                }
                outJsonArray.append(ticket);
            }



    }
    qDebug()<<"transfer ok";
    }

    else{
         qDebug()<<"transfer fail";
    }
}

void service::payOrder(QJsonObject &inJson, QJsonArray &outJsonArray)
{
    QString orderId=inJson.value("orderId").toString();
//    QSqlQuery query(db);
//    query.prepare("select count(order_id) from tickets.order_pass where order_id =? and ticket_status !='已退票' ");
//    query.addBindValue(orderId);
//    if(query.exec()){
//        if(query.first()){
//            if(query.value(0).toInt()!=0){

//            }else{//全部退票

//            }
//        }
//    }else{

//    }
    QSqlQuery infoQuery(db);
    infoQuery.prepare("update train_tickets.order_info set order_status ='已完成' where order_id= ? and order_status !='已失效'");
    infoQuery.addBindValue(orderId);
    if(infoQuery.exec()){

    QSqlQuery passQuery(db);
    passQuery.prepare("update train_tickets.order_pass set ticket_status = '已支付' where order_id =? and ticket_status !='已退票'");
    passQuery.addBindValue(orderId);
    if(passQuery.exec()){
        qDebug()<<"pay success";
        outJsonArray.append(true);
    }else{
        qDebug()<<"pay info fail";
        outJsonArray.append(false);
    }
    }else{
        qDebug()<<"pay pass fail";
        outJsonArray.append(false);
    }

}
void service::debug(QJsonObject &dataIn, QJsonArray &dataOut)
{
    int res=dataIn.value("request").toInt();
    QString temp=QString::number(res);
    qDebug()<<"request"<<temp;
    dataOut.append(false);
}

//                       QString checkStr;
//                       for(int i=order1;i<=order2;i++){
//                           checkStr+="1";
//                       }


//                       //如果该座位的 order1-order2的数字全为1，则有票
//                       if(free.mid(order1-1,order2-1)==checkStr){
//                           if(coach==1){
//                               ticketsNum0++;
//                           }else if(coach>=2&&coach<=3){
//                               ticketsNum1++;
//                           }else{
//                               ticketsNum2++;
//                           }
//                       }else {
//                              qDebug("no ticket");
//                       }


//               //制作需要的bit串
//               int strNum;
//               QString str4=QString("select count(train_id) from train_tickets.pass_by where train_id=?");
//               QSqlQuery query4(db);

//               query4.prepare(str4);
//               query4.addBindValue(tid);
//               query4.addBindValue(stationFrom);

//                if(query4.exec()){
//                    strNum=query4.value(0).toInt();
//                    QString freeArray;

//                    for(int i=0;i<strNum;i++){
//                        if(i>=order1-1||i<=order2-1){
//                            freeArray+="1";
//                        }else{
//                            freeArray+="0";
//                        }
//                       }

//                }else{
//                     qDebug("find strNum fail");
//                      outJsonArray.append(false);
//                      return;
//                }
//                //比对 free 和freeArray
