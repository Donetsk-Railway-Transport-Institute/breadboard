//начальная инициализация
function first_init(param)
{
    G.run("./xml/play/init.js");
    G.create_train("0001", "Луговая:1П");
    G.first_help();
}

function button_press(button)
{
//    G.msg_to_log("button_press("+button+")");
    //если поезд прибыл на 2-й путь ст.Луговая, а кнопка "путевое прибытие не нажата", 
    //то нет окончания игры. После начатия "дача прибытия" заканчиваем игру
    if(button=="ПУЛЬТ_Луговая:ДП") //нажатие кнопки "дача прибытия"
    {
        if((G.head_train("0001")=="Луговая:2П")&&(G.tail_train("0001")=="Луговая:2П")) game_over("Луговая:2П");
    }
}

//оценка критерия окончания игры 
function game_over(signal)
{
//    G.msg_to_log("game_over("+signal+")");
    if(signal=="Луговая:2П") //критерий окончания - поезд на 2-м пути
    { 
        if((G.s("Горная:ПП")==0)&&(G.s("Луговая:ПП")==0)&&(G.head_train("0001")=="Луговая:2П")&&(G.tail_train("0001")=="Луговая:2П")) G.w_game_ower();
    }
}
