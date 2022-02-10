//начальная инициализация
function first_init(param)
{
    G.run("./xml/play/init.js");
    G.create_train("0001", "Горная:1П");
    G.create_train("0002", "Горная:3П");
    G.first_help();
}

function button_press(button)
{
//    G.msg_to_log("button_press("+button+")");
    //если поезд прибыл на 2-й путь ст.Луговая, а кнопка "путевое прибытие не нажата", 
    //то нет окончания игры. После начатия "дача прибытия" заканчиваем игру
    if(button=="ПУЛЬТ_Горная:ДП") //нажатие кнопки "дача прибытия"
    {
        if((G.head_train("0001")=="Горная:2П")&&(G.tail_train("0001")=="Горная:2П")) game_over("Горная:2П");
        if((G.head_train("0002")=="Горная:3П")&&(G.tail_train("0002")=="Горная:3П")) game_over("Горная:3П");
    }
}

//оценка критерия окончания игры 
function game_over(signal)
{
//    G.msg_to_log("game_over("+signal+")");
//    G.msg_to_log("\t\thead_train(0001)="+G.head_train("0001"));
//    G.msg_to_log("\t\ttail_train(0001)="+G.tail_train("0001"));
//    G.msg_to_log("\t\thead_train(0002)="+G.head_train("0002"));
//    G.msg_to_log("\t\ttail_train(0002)="+G.tail_train("0002"));
    if((G.s("Горная:ПП")==0)&&(G.s("Луговая:ПП")==0)&&
        (G.head_train("0001")=="Горная:3П")&&
        (G.tail_train("0001")=="Горная:3П")&&
        (G.head_train("0002")=="Горная:2П")&&
        (G.tail_train("0002")=="Горная:2П")) G.w_game_ower();
}
