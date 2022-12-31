#ifndef VALIDATE_H
#define VALIDATE_H
#include<iostream>
#include <QString>
#include <string.h>

class validate
{

private:
    bool is_empty(QString data)
    {
        return data.trimmed().isEmpty();
    }

    bool contain_number(QString name)
    {
        std::string name_str = name.toStdString();
        if(name_str.size()<3)
            return false;
        for(int i = 0; i < name_str.size(); i++){
            if(!isalpha(name_str[i]))
                return false;
        }
        return true;
    }

    bool contain_letter(QString phone){
        std::string phone_str = phone.toStdString();
        if(phone_str.size() != 11)
            return false;
        if(phone_str.substr(0, 2) != "01")
            return false;
        for(int i = 0;i < phone_str.size(); i++){
            if(!isdigit(phone_str[i]))
                return false;
        }
        return true;
    }

    bool email_validate_helper(QString email){
        if(email.size() < 10)
            return false;
        for(int i = 0; i < email.size(); i++){
            if(email[i] == '@')
                return true;
        }
        return false;
    }


public:

    bool name_validate(const QString name){
        if(is_empty(name) || contain_number(name))
            return false;
        return true;
    }

    bool department_validate(QString department){
        return(!is_empty(department));
    }

    bool email_validate(QString email){
        return(email_validate_helper(email));
    }

    bool phone_validate(QString phone){
        return(!is_empty(phone) && contain_letter(phone));
    }

    bool title_validate(QString title){
        return(!is_empty(title));
    }

    bool biography_validate(QString biography){
        return(!is_empty(biography));
    }

    bool password_validate(QString password){
        return(!is_empty(password));
    }

    bool type_validate(QString type){
        return(!is_empty(type));
    }

    bool hall_validate(QString hall){
        return(!is_empty(hall));
    }

    bool course_name_validate(QString name){
        return(is_empty(name));
    }


};













#endif // VALIDATE_H
