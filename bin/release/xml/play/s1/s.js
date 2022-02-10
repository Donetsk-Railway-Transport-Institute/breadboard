//начальная инициализация
function first_init(param)
{
    G.run(param);
    G.create_train("0001", "Горная:3П");
    G.first_help();
}


function button_press(button)
{
//    G.msg_to_log("button_press("+button+")");
    if(button=="ПУЛЬТ_Горная:ДП") //критерий окончания - нажатие кнопки "дача прибытия"
    {
        //если поезд на 1-м пути
        if((G.head_train("0001")=="Горная:1П")&&(G.tail_train("0001")=="Горная:1П")) G.w_game_ower();
    }
}

//оценка критерия окончания игры 
function game_over(signal)
{
//    G.msg_to_log("game_over("+signal+")");
    if(signal=="Горная:1П") //критерий окончания - прибытие поезда на 1-й путь
    {
        if((G.s("Горная:ПП")==0)&&(G.s("Луговая:ПП")==0)) G.w_game_ower();
    }
}




