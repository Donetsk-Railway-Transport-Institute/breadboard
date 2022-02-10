//начальная инициализация
function first_init(param)
{
    G.run(param);
    G.create_train("0001", "Горная:1П");
    G.first_help();
}


function button_press(button)
{
//    G.msg_to_log("button_press("+button+")");
}

//оценка критерия окончания игры 
function game_over(signal)
{
//    G.msg_to_log("game_over("+signal+")");
}




