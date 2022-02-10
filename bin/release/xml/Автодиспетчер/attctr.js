//начальная инициализация
//param - режим, в котором работает программа
function first_init(param)
{
    A.msg_to_log("Горная first_init run as "+param);
    A.set_sycle_num(0);
    A.send_ctr_panel("ПУЛЬТ_Горная:Н1");
    A.send_ctr_panel("ПУЛЬТ_Горная:Ч");
}

//Сигнал для перерисовки объекта в новом состоянии
function set_new_sost(sost)
{
    A.msg_to_log("set_new_sost("+sost+")");
    if(A.get_sycle_num()==0)
    {  
        if(sost=="Горная:2-4СП:3")
        {
	    A.send_ctr_panel("ПУЛЬТ_Луговая:Н");
        }
        //Нажимаем конечную поездную кнопку

        if(sost=="Горная:2-4СП:1")
        {
            A.send_ctr_panel("ПУЛЬТ_Луговая:Ч1"); 
        }
        if(sost=="Горная-Луговая:2П:1")
        {
	    A.send_ctr_panel("ПУЛЬТ_Горная:ПДС");
            A.send_ctr_panel("ПУЛЬТ_Луговая:Н1");        
        }
        if(sost=="Луговая:1СП:1")       	
    	{     		
	    A.send_ctr_panel("ПУЛЬТ_Луговая:Ч");
    	}
	if(sost=="Луговая:1П:1") 
      	{
		A.send_ctr_panel("ПУЛЬТ_Горная:Н");
    	}
	if(sost=="Луговая-Горная:ЧН2:1")
    	{
		A.send_ctr_panel("ПУЛЬТ_Горная:Ч1");
    	}
        if(sost=="Горная:1-3СП:2")
       	{
		A.send_ctr_panel("ПУЛЬТ_Горная:ДП");
   		A.send_ctr_panel("ПУЛЬТ_Луговая:ПДС");                
                A.set_sycle_num(1);
                A.send_ctr_panel("ПУЛЬТ_Горная:Ч1");
        }
    }
    //делаем круг в обратную сторону
    if(A.get_sycle_num()==1)
    {  

        if(sost=="Горная:ИЗМЧ:1")
        {
            A.send_ctr_panel("ПУЛЬТ_Горная:Н");
        }
    }
}	

//Сигнал для установки нового состояния напольных устройств
function set_sost_from_at(sost)
{
    A.msg_to_log("set_sost_from_at("+sost+")");

}

//Сигнал для установки нового состояния повторителя
function set_new_bind_sost(sost)
{
    A.msg_to_log("set_new_bind_sost("+sost+")");
}

//Сигнал для отслеживания манипуляций пользователя с
//контрольной панелью (ввод команд оператором)
function change_control_panel_sost(sost)
{
    A.msg_to_log("change_control_panel_sost("+sost+")");
}




