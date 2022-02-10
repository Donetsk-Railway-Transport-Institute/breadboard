//Первоначальная инициализация состояния объектов
function first_init(param)
{
//    AT.msg_to_log("Луговая-Горная first_init("+param+")");
}

//Функция вызывается из слота void set_sost(const QString &str_sost)
function change_sost(obj_name)
{
//    AT.msg_to_log("Луговая-Горная change_sost("+obj_name+")");
    var s = AT.spl(obj_name);
    var int_sost = AT.to_int(s[2]);

    //Трансляция команд с задержкой на включение(выключение) тягового тока
    if(AT.indexOf(s[1],"Т")==0) AT.set_sost_from_at(obj_name);

    //переход в исходное состояние перегона после подачи "Дача прибытия"
    if((s[1]=="СН")&&(int_sost==0)){
        AT.set_new_bind_sost("Луговая:ПС:"+s[2]);
        AT.set_new_bind_sost("Горная:ПС:"+s[2]);
    }

    //если установлено нечетное направление
    if(AT.s("СН")==1)
    {
        if(s[1]=="ПН") //Повторитель входного Н ст.Горная
        {
            if((AT.s("ЧН1")==1)&&(int_sost>1)) //если занят участок перед входным, и открывается светофор - включаем тягу
                AT.sleep_signal("Луговая-Горная:ТЧН1:1", 1000); 
        }
        if(s[1]=="ЧН2")
        {
            //поезд занимает участок ЧН2 (первый участок удаления ст.Луговая), подаем тяговый ток
            if(int_sost==1) AT.set_sost_from_at("Луговая-Горная:ТЧН2:1");
            //освобождение участка ЧН2, выключаем тяговый ток
            if(int_sost==2) AT.set_sost_from_at("Луговая-Горная:ТЧН2:0");
        }
        if(s[1]=="ЧН3")
        {
            //поезд занимает участок ЧН3 (второй участок удаления ст.Луговая), подаем тяговый ток
            if(int_sost==1) AT.set_sost_from_at("Луговая-Горная:ТЧН3:1");
            //освобождение участка ЧН2, выключаем тяговый ток
            if(int_sost==2) AT.set_sost_from_at("Луговая-Горная:ТЧН3:0");
        }
        if(s[1]=="ЧН1")
        {
            //поезд занимает участок ЧН1 (участок перед светофором Н ст.Горная), подаем тяговый ток
            if(int_sost==1) 
            {
                AT.set_sost_from_at("Луговая-Горная:ТЧН1:1");
                //если входной Н закрыт, то ток выключаем с задержкой 90% от времени проследования ЧН1
                if(AT.ss("Луговая-Горная:ПН")<2) AT.sleep_signal("Луговая-Горная:ТЧН1:0",AT.m_time("ЧН1",90)); 
            }
            //освобождение участка ЧН1, выключаем тяговый ток
            if(int_sost==2) AT.set_sost_from_at("Луговая-Горная:ТЧН1:0");
        }
    }
    //если установлено четное направление
    if(AT.s("СН")==2)
    {
        if(s[1]=="ПЧ") //Повторитель входного Ч ст.Луговая
        {
            if((AT.s("ЧН2")==1)&&(int_sost>1)) //если занят участок перед входным, и открывается светофор - включаем тягу
                AT.sleep_signal("Луговая-Горная:ТЧН2:2", 1000); 
        }
        if(s[1]=="ЧН1")
        {
            //поезд занимает участок ЧН1 (первый участок удаления ст.Горная), подаем тяговый ток
            if(int_sost==1) AT.set_sost_from_at("Луговая-Горная:ТЧН1:2");
            //освобождение участка ЧН1, выключаем тяговый ток
            if(int_sost==2) AT.set_sost_from_at("Луговая-Горная:ТЧН1:0");
        }
        if(s[1]=="ЧН3")
        {
            //поезд занимает участок ЧН3 (второй участок удаления ст.Горная), подаем тяговый ток
            if(int_sost==1) AT.set_sost_from_at("Луговая-Горная:ТЧН3:2");
            //освобождение участка ЧН2, выключаем тяговый ток
            if(int_sost==2) AT.set_sost_from_at("Луговая-Горная:ТЧН3:0");
        }
        if(s[1]=="ЧН2")
        {
            //поезд занимает участок ЧН2 (участок перед светофором Ч ст.Луговая), подаем тяговый ток
            if(int_sost==1) 
            {
                AT.set_sost_from_at("Луговая-Горная:ТЧН2:2");
                //если входной Ч закрыт, то ток выключаем с задержкой 90% от времени проследования ЧН2
                if(AT.ss("Луговая-Горная:ПЧ")<2) AT.sleep_signal("Луговая-Горная:ТЧН2:0",AT.m_time("ЧН2",90)); 
            }
            //освобождение участка ЧН2, выключаем тяговый ток
            if(int_sost==2) AT.set_sost_from_at("Луговая-Горная:ТЧН2:0");
        }
    }

    //отображаем в новом состоянии
    AT.set_new_sost(s[0]+":"+s[1], int_sost);    
}

