#include "logincontroller.h"

LoginController::LoginController(QObject *parent):QObject(parent){
    mapper = new MangerMapper();
}
LoginController::~LoginController(){

}
bool LoginController::tryLogin(const QString &id,const QString &password){
   if(mapper->judgePassword(id,password)){
       username = id;
       tools::get_instance()->recordOperation("登录","用户"+username+"登录成功",username,QDateTime::currentDateTime());
       return true;
   }else{
       return false;
   }
}
