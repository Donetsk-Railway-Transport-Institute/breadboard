//обработка команд напольным устройствам
function move_train(signal)
{
    var s = G.spl(signal);
//    G.msg_to_log("move_train("+signal+")");
    //Получение названия элемента пути, для которого вкл/выкл тяга
    var obj = G.spl(s[1],"Т")[1];
    //выключение тяги
    if(s[2]=="0") return G.power_off(s[0]+":"+obj);
    if(s[2]=="1")
    {
        if(s[0]=="Горная")
        {
            if(obj=="1-3СП")
            {
                //следующий участок в зависимости от положения стрелки
                if((G.s("Горная:1")==1)&&(G.s("Горная:3")==1)) G.power_on(s[0]+":"+obj, "Горная:1П");
                if((G.s("Горная:1")==1)&&(G.s("Горная:3")==2)) G.power_on(s[0]+":"+obj, "Горная:2П");
                if(G.s("Горная:1")==2) G.power_on(s[0]+":"+obj, "Горная:3П");
            }
            //включаем тягу в 1П или 3П, следующий участок, на который переместится поезд - 2-4СП
            if((obj=="1П")&&(G.s("Горная:Н1")>1)) G.power_on(s[0]+":"+obj, "Горная:2-4СП");
            if((obj=="3П")&&(G.s("Горная:Н3")>1)) G.power_on(s[0]+":"+obj, "Горная:2-4СП");
            if(obj=="2-4СП") G.power_on(s[0]+":"+obj, "Горная-Луговая:2П");
        }
        if(s[0]=="Горная-Луговая")
        {
            if(obj=="2П") G.power_on(s[0]+":"+obj, "Горная-Луговая:3П");
            if(obj=="3П") G.power_on(s[0]+":"+obj, "Горная-Луговая:1П");
            if(obj=="1П") G.power_on(s[0]+":"+obj, "Луговая:1СП");
        }
        if(s[0]=="Луговая")
        {
            if(obj=="1СП")
            {
                //следующий участок в зависимости от положения стрелки
                if(G.s("Луговая:1")==1) G.power_on(s[0]+":"+obj, "Луговая:1П");
                if(G.s("Луговая:1")==2) G.power_on(s[0]+":"+obj, "Луговая:2П");
            }
            if((obj=="1П")&&(G.s("Луговая:Н1")>1)) G.power_on(s[0]+":"+obj, "Луговая:2СП");
            if((obj=="2П")&&(G.s("Луговая:Н2")>1)) G.power_on(s[0]+":"+obj, "Луговая:2СП");
            if(obj=="2СП") G.power_on(s[0]+":"+obj, "Луговая-Горная:ЧН2");
        }
        if(s[0]=="Луговая-Горная")
        {
            if(obj=="ЧН2") G.power_on(s[0]+":"+obj, "Луговая-Горная:ЧН3");
            if(obj=="ЧН3") G.power_on(s[0]+":"+obj, "Луговая-Горная:ЧН1");
            if(obj=="ЧН1") G.power_on(s[0]+":"+obj, "Горная:1-3СП");
        }
    }
    if(s[2]=="2")
    {
        if(s[0]=="Горная")
        {
            if(obj=="2-4СП")
            {
                //следующий участок в зависимости от положения стрелки
                if((G.s("Горная:2")==1)&&(G.s("Горная:4")==1)) G.power_on(s[0]+":"+obj, "Горная:1П");
                if((G.s("Горная:2")==1)&&(G.s("Горная:4")==2)) G.power_on(s[0]+":"+obj, "Горная:3П");
                if(G.s("Горная:2")==2) G.power_on(s[0]+":"+obj, "Горная:2П");
            }
            //включаем тягу в 1П или 2П, следующий участок, на который переместится поезд - 1-3СП
            if((obj=="1П")&&(G.s("Горная:Ч1")>1)) G.power_on(s[0]+":"+obj, "Горная:1-3СП");
            if((obj=="2П")&&(G.s("Горная:Ч2")>1)) G.power_on(s[0]+":"+obj, "Горная:1-3СП");
            if(obj=="1-3СП") G.power_on(s[0]+":"+obj, "Луговая-Горная:ЧН1");
        }
        if(s[0]=="Луговая-Горная")
        {
            if(obj=="ЧН1") G.power_on(s[0]+":"+obj, "Луговая-Горная:ЧН3");
            if(obj=="ЧН3") G.power_on(s[0]+":"+obj, "Луговая-Горная:ЧН2");
            if(obj=="ЧН2") G.power_on(s[0]+":"+obj, "Луговая:2СП");
        }
        if(s[0]=="Луговая")
        {
            if(obj=="2СП")
            {
                //следующий участок в зависимости от положения стрелки
                if(G.s("Луговая:2")==1) G.power_on(s[0]+":"+obj, "Луговая:1П");
                if(G.s("Луговая:2")==2) G.power_on(s[0]+":"+obj, "Луговая:2П");
            }
            if((obj=="1П")&&(G.s("Луговая:Ч1")>1)) G.power_on(s[0]+":"+obj, "Луговая:1СП");
            if((obj=="2П")&&(G.s("Луговая:Ч2")>1)) G.power_on(s[0]+":"+obj, "Луговая:1СП");
            if(obj=="1СП") G.power_on(s[0]+":"+obj, "Горная-Луговая:1П");
        }
        if(s[0]=="Горная-Луговая")
        {
            if(obj=="1П") G.power_on(s[0]+":"+obj, "Горная-Луговая:3П");
            if(obj=="3П") G.power_on(s[0]+":"+obj, "Горная-Луговая:2П");
            if(obj=="2П") G.power_on(s[0]+":"+obj, "Горная:2-4СП");
        }

    }
}