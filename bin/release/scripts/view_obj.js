function bottom_ellipse_0(param){
    //Кнопка
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    var color_name = SC.curr_color_name;
    SC.curr_color_name = "darkGray"
    SC.set_pen(SC.curr_color_name, w/8);
    SC.drawEllipse(x,y+w/4,3*w/7+1);
    SC.curr_color_name = color_name
    SC.set_pen(SC.curr_color_name, w/8);
    SC.beginPath();
    SC.addEllipse(x,y+w/4,3*w/7+1);
    SC.fillPath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
}

function bottom_ellipse_180(param){
    //Кнопка
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    var color_name = SC.curr_color_name;
    SC.curr_color_name = "darkGray"
    SC.set_pen(SC.curr_color_name, w/8);
    SC.drawEllipse(x+w/2,y+w/4,3*w/7+1);
    SC.curr_color_name = color_name
    SC.set_pen(SC.curr_color_name, w/8);
    SC.beginPath();
    SC.addEllipse(x+w/2,y+w/4,3*w/7+1);
    SC.fillPath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
}

function bottom_track(param){
    //количество состояний и соответствующих им цветов отображения
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    //выравнивание текста надписи
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    
    //если angle==0 сначала надпись, потом кнопка
    //если angle==180 сначала кнопка, потом надпись
    var angle  = SC.get_int_attr("angle");
    
    //получение размера отображения надписи
    var count_pics_name = SC.get_pix_count_cells(0);
    
    //проход по ячейкам отображения
    for(column=0;column<count_pics_name+1;column++)
    {
        //создаем ячейку отображения
        SC.create_cell();
        //проход по возможным состояниям отображения
        for(i=0;i<COUNT_SIGNAL_SOST;i++)
        {        
            if(angle==180)
                if(column==0) SC.cell_draw_pix("bottom_ellipse_180",SC.get_color_sost(i),SC.get_color_background_sost(i));
                else SC.cell_draw_text(column-1,"darkBlue",SC.get_color_background_sost(i),2); //Qt::AlignRight
            if(angle==0)
                if(column==count_pics_name) SC.cell_draw_pix("bottom_ellipse_0",SC.get_color_sost(i),SC.get_color_background_sost(i));
                else SC.cell_draw_text(column,"darkBlue",SC.get_color_background_sost(i),1); //Qt::AlignLeft;
            //добавляем созданный рисунок в ячейку отображения
            SC.add_pix_to_cell();
        }
        //добавляем созданную ячейку в массив
        SC.add_cell_to_array(x+column,y);
    }
    
    						
}

function cell_one_line(param){
    //одна линия соответствующим цветом посреди клетки
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function cell_one_line_1(param){
    //одна линия соответствующим цветом посреди клетки
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(w/2,0,w/2,w);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function cell_one_line_vert(param){
    //одна линия соответствующим цветом посреди клетки
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/8);
    SC.draw_line(w/2,w/4,w/2,3*w/4);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function cell_one_line_vert_full(param){
    //одна линия соответствующим цветом посреди клетки
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/8);
    SC.draw_line(w/2,0,w/2,w);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function deadlock(param){
    //Тупик
    var angle  = SC.get_int_attr("angle");
    var script_name;
    if (angle==0) script_name="deadlock_left";
    if (angle==180) script_name="deadlock_right";
    
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_DEADLOCK_SOST = SC.get_count_color_sost();
    
    SC.create_cell();
    for(i=0;i<COUNT_DEADLOCK_SOST;i++) 
    {
    	SC.cell_draw_pix(script_name,SC.get_color_sost(i),SC.get_color_background_sost(i));
    	SC.add_pix_to_cell();
    }
    SC.add_cell_to_array(x,y);
}

function deadlock_left(param){
    //тупик влево
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(w,w/2,4*w/5,w/2);
    SC.set_pen(SC.curr_color_name, w/10);
    SC.draw_line(w/2,w/4,3*w/4,w/4);
    SC.draw_line(3*w/4,w/4,3*w/4,3*w/4);
    SC.draw_line(3*w/4,3*w/4,w/2,3*w/4);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function deadlock_right(param){
    //тупик вправо
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w/5,w/2);
    SC.set_pen(SC.curr_color_name, w/10);
    SC.draw_line(w/4,w/4,w/2,w/4);
    SC.draw_line(w/4,w/4,w/4,3*w/4);
    SC.draw_line(w/4,3*w/4,w/2,3*w/4);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
}

function direction_of_peregon(param){
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    for(count=0;count<4;count++)
    {
        SC.create_cell();
        for(i=0;i<COUNT_SIGNAL_SOST;i++)
        {
            var script_name;	
            switch (count) {
                case 0:
                    if((i==0)||(i==2)||(i==4)) script_name = "triangle_up";
                    else script_name = "cell_one_line_vert_full";
                    break;
                case 1:
                    script_name = "cell_one_line_vert_full";
                    break;
                case 2:
                    script_name = "cell_one_line_vert_full";
                    break;
                case 3:
                    if((i==0)||(i==1)||(i==3)) script_name = "triangle_down";
                    else script_name = "cell_one_line_vert_full";
                    break;
                default:
                    break;
            }
            SC.cell_draw_pix(script_name,SC.get_color_sost(i),SC.get_color_background_sost(i));
            SC.add_pix_to_cell();
        }
        SC.add_cell_to_array(x,y+count);
    }
}

function direction_of_peregon_pab(param){
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    for(count=0;count<4;count++)
    {
        SC.create_cell();
        for(i=0;i<COUNT_SIGNAL_SOST;i++)
        {
            var script_name;	
            switch (count) {
                case 0:
                    if((i==0)||(i==1)||(i==3)) script_name = "triangle_up";
                    else script_name = "cell_one_line_vert_full";
                    break;
                case 1:
                    script_name = "cell_one_line_vert_full";
                    break;
                case 2:
                    script_name = "cell_one_line_vert_full";
                    break;
                case 3:
                    if((i==0)||(i==2)||(i==4)) script_name = "triangle_down";
                    else script_name = "cell_one_line_vert_full";
                    break;
                default:
                    break;
            }
            SC.cell_draw_pix(script_name,SC.get_color_sost(i),SC.get_color_background_sost(i));
            SC.add_pix_to_cell();
        }
        SC.add_cell_to_array(x,y+count);
    }
}

function direction_of_stantion(param){
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var d = SC.get_int_attr("direction");
    
    for(x_cell=0;x_cell<2;x_cell++)
    {
        SC.create_cell();
        for(i=0;i<COUNT_SIGNAL_SOST;i++)
        {
            if(i==0)
            {
                if(x_cell==0) SC.cell_draw_pix("triangle_left",SC.get_color_sost(i),SC.get_color_background_sost(i));
                else SC.cell_draw_pix("triangle_right",SC.get_color_sost(i),SC.get_color_background_sost(i));
            }
            else 
            {
                if(d==0)
                {
                    if(x_cell==0)
                    {
                        if(i%2==0) script_name = "cell_one_line";
                        else script_name = "triangle_left";
                    }
                    else
                    {
                        if(i%2==0) script_name = "triangle_right";
                        else script_name = "cell_one_line";
                    }
                }
                else
                {
                    if(x_cell==0)
                    {
                        if(i%2==0) script_name = "triangle_left";
                        else script_name = "cell_one_line";
                    }
                    else
                    {
                        if(i%2==0) script_name = "cell_one_line";
                        else script_name = "triangle_right";
                    }
                }
                SC.cell_draw_pix(script_name,SC.get_color_sost(i),SC.get_color_background_sost(i));
            }
            SC.add_pix_to_cell();
        }
        SC.add_cell_to_array(x+x_cell,y);
    }
}

function indicator_length_as_name(param){
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var count_draw_cell = SC.get_pix_count_cells(4);
    for(count=0;count<count_draw_cell;count++)
    {
        SC.create_cell();
        for(i=0;i<COUNT_SIGNAL_SOST;i++)    
        {
            SC.cell_draw_text(count,SC.get_color_sost(i),SC.get_color_background_sost(i),4);
            SC.add_pix_to_cell();
        }
        SC.add_cell_to_array(x+count,y);
    }
}

function indicator_s_routes_left(param){
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    for(count=0;count<2;count++)
    {
        SC.create_cell();
        for(i=0;i<COUNT_SIGNAL_SOST;i++)
        {
            var script_name;	
            var color_sost = i;
            if(count==0) {
                if((i==1)||(i==3)) color_sost = 0;
                script_name = "triangle_left_half";
            }
            else script_name = "triangle_left_half_left";
            SC.cell_draw_pix(script_name,SC.get_color_sost(color_sost),SC.get_color_background_sost(i));
            SC.add_pix_to_cell();
        }
        SC.add_cell_to_array(x+count,y);
    }
}

function indicator_s_routes_rigth(param){
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    for(count=0;count<2;count++)
    {
        SC.create_cell();
        for(i=0;i<COUNT_SIGNAL_SOST;i++)
        {
            var script_name;	
            var color_sost = i;
            if(count==0) script_name = "triangle_rigth_half_rigth";
            else {
                if((i==1)||(i==3)) color_sost = 0;
                script_name = "triangle_rigth_half";
            }
            SC.cell_draw_pix(script_name,SC.get_color_sost(color_sost),SC.get_color_background_sost(i));
            SC.add_pix_to_cell();
        }
        SC.add_cell_to_array(x+count,y);
    }
}

function signal(param){
    //количество состояний и соответствующих им цветов отображения
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    //выравнивание текста надписи
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var angle  = SC.get_int_attr("angle");
    var invitation  = SC.get_int_attr("invitation");
    if (angle==0) 
    {
    	//надпись начнет выводится с 0-й ячейки, с выравниванием направо
    	var aligned=2;					//Qt::AlignRight
    	var name_first = "signal_right";
    	var name_two = "signal_right_two";
    }
    if (angle==180) 
    {
    	//надпись начнет выводится с 1-й ячейки, если светофор с одной головкой,
    	//или со 2-й, если с двумя, текст выравнивается влево
    	var aligned=1					//Qt::AlignLeft;
    	var name_first = "signal_left";
    	var name_two = "signal_left_two";
    }
    //получение размера отображения надписи
    var count_pics_name = SC.get_pix_count_cells(0);
    //проход по ячейкам отображения
    for(column=0;column<count_pics_name+invitation+1;column++)
    {
    	//создаем ячейку отображения
    	SC.create_cell();
    	//проход по возможным состояниям отображения
    	for(i=0;i<COUNT_SIGNAL_SOST;i++)
    	{	
    		var name;
    		var curr_color;
    		if(aligned==2)	//светофор направо
    		{
    			//если выводить надпись
    			if(column<count_pics_name) 
    			{
    				if(i==0) SC.cell_draw_text(column,"darkGray",SC.get_color_background_sost(i),aligned);
    				else SC.cell_draw_text(column,"darkBlue",SC.get_color_background_sost(i),aligned);
    			}
    			else
    			{
    				if(column==count_pics_name)
    				{
    					//первая ячейка после надписи и если светофор с одной головкой
    					if(invitation==0) curr_color = (i<COUNT_SIGNAL_SOST-1)?SC.get_color_sost(i):SC.get_color_sost(0);
    					else curr_color = (i<COUNT_SIGNAL_SOST-1)?SC.get_color_sost(0):SC.get_color_sost(i);
    					name = name_first;
    				}
    				else 
    				{
    					//втораяая ячейка после надписи (светофор с двумя головками)
    					curr_color = (i<COUNT_SIGNAL_SOST-1)?SC.get_color_sost(i):SC.get_color_sost(0);
    					name = name_two;
    				}
    				SC.cell_draw_pix(name, curr_color,SC.get_color_background_sost(i));
    			}
    		}
    		else if(aligned==1)	//светофор налево
    		{
    			if(column>invitation)
    			{
    				//если надпись
    				if(i==0) SC.cell_draw_text(column-invitation-1,"darkGray",SC.get_color_background_sost(i),aligned);
    				else SC.cell_draw_text(column-invitation-1,"darkBlue",SC.get_color_background_sost(i),aligned);
    			}
    			else
    			{				
    				if(column==0)
    				{
    					//первая ячейка
    					curr_color = (i<COUNT_SIGNAL_SOST-1)?SC.get_color_sost(i):SC.get_color_sost(0);
    					name = (invitation==0)?name_first:name_two;
    				}
    				else
    				{
    					//втораяая ячейка (светофор с двумя головками)
    					curr_color = (i<COUNT_SIGNAL_SOST-1)?SC.get_color_sost(0):SC.get_color_sost(i);
    					name = name_first;
    				}
    				SC.cell_draw_pix(name, curr_color,SC.get_color_background_sost(i));
    			}
    		}		
    		//добавляем созданный рисунок в ячейку отображения
    		SC.add_pix_to_cell();
    	}
    	//добавляем созданную ячейку в массив
    	SC.add_cell_to_array(x+column,y);
    }
    
    						
}

function signal_ab(param){
    //светофор АБ
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var orient = SC.get_int_attr("orientation");
    SC.create_cell();
    for(i=0;i<COUNT_SIGNAL_SOST;i++)
    {	
    	if(orient==0) SC.cell_draw_pix("triangle_down",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	if(orient==1) SC.cell_draw_pix("triangle_up",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	SC.add_pix_to_cell();
    }
    SC.add_cell_to_array(x,y);
    
    
}

function signal_left(param){
    //Светофор с одной головкой в левую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    
    var color_name = SC.curr_color_name;
    SC.curr_color_name = "darkGray"
    SC.set_pen(SC.curr_color_name, w/8);
    SC.drawLine(x+4*w/5,y+w/5,x+4*w/5,y+4*w/5);
    SC.drawLine(x+4*w/5,y+w/2,x+3*w/5,y+w/2);
    SC.drawEllipse(x+1,y+w/5,3*w/5+1);
    SC.curr_color_name = color_name
    SC.set_pen(SC.curr_color_name, w/8);
    SC.beginPath();
    SC.addEllipse(x+1,y+w/5,3*w/5+1);
    SC.fillPath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
}

function signal_left_two(param){
    //Вторая головка светофора в левую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    
    var color_name = SC.curr_color_name;
    SC.curr_color_name = "darkGray"
    SC.set_pen(SC.curr_color_name, w/8);
    SC.drawEllipse(x+2*w/5-1,y+w/5,3*w/5-1);
    SC.curr_color_name = color_name
    SC.set_pen(SC.curr_color_name, w/8);
    SC.beginPath();
    SC.addEllipse(x+2*w/5-1,y+w/5,3*w/5-1);
    SC.fillPath();
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
}

function signal_right(param){
    ////Светофор с одной головкой в правую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    
    var color_name = SC.curr_color_name;
    SC.curr_color_name = "darkGray"
    SC.set_pen(SC.curr_color_name, w/8);
    SC.drawLine(x+w/5,y+w/5,x+w/5,y+4*w/5);
    SC.drawLine(x+w/5,y+w/2,x+2*w/5,y+w/2);
    SC.drawEllipse(x+2*w/5-1,y+w/5,3*w/5-1);
    SC.curr_color_name = color_name
    SC.set_pen(SC.curr_color_name, w/8);
    SC.beginPath();
    SC.addEllipse(x+2*w/5-1,y+w/5,3*w/5-1);
    SC.fillPath();
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
}

function signal_right_two(param){
    //Вторая головка светофора в правую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    
    var color_name = SC.curr_color_name;
    SC.curr_color_name = "darkGray"
    SC.set_pen(SC.curr_color_name, w/8);
    SC.drawEllipse(x+1,y+w/5,3*w/5+1);
    SC.curr_color_name = color_name
    SC.set_pen(SC.curr_color_name, w/8);
    SC.beginPath();
    SC.addEllipse(x+1,y+w/5,3*w/5+1);
    SC.fillPath();
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
}

function signal_shunting(param){
    //Маневровый светофор
    //количество состояний и соответствующих им цветов отображения
    var COUNT_SIGNAL_SOST = SC.get_count_color_sost();
    //выравнивание текста надписи
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var angle  = SC.get_int_attr("angle");
    var aligned;
    //Маневровый сигнал
    //надпись начнет выводится с 0-й ячейки, с выравниванием направо
    if (angle==0) aligned=2; //Qt::AlignRight
    
    //надпись начнет выводится с 1-й ячейки, текст выравнивается влево
    if (angle==180) aligned=1; //Qt::AlignLeft;
    
    //получение размера отображения надписи
    var count_pics_name = SC.get_pix_count_cells(0);
    //проход по ячейкам отображения
    for(column=0;column<count_pics_name+1;column++)
    {
    	//создаем ячейку отображения
    	SC.create_cell();
    	//проход по возможным состояниям отображения
    	for(i=0;i<COUNT_SIGNAL_SOST;i++)
    	{	
    		var curr_color;
    		if(aligned==2)	//светофор направо
    		{
    			//если выводить надпись
    			if(column<count_pics_name) 
    			{
    				if(i==0) SC.cell_draw_text(column,"darkGray",SC.get_color_background_sost(i),aligned);
    				else SC.cell_draw_text(column,"darkBlue",SC.get_color_background_sost(i),aligned);
    			}
    			else
    			{
    				//первая ячейка после надписи
    				SC.cell_draw_pix("signal_right",SC.get_color_sost(i),SC.get_color_background_sost(i));
    			}
    		}
    		else if(aligned==1)	//светофор налево
    		{
    			if(column>0)
    			{
    				//если надпись
    				if(i==0) SC.cell_draw_text(column-1,"darkGray",SC.get_color_background_sost(i),aligned);
    				else SC.cell_draw_text(column-1,"darkBlue",SC.get_color_background_sost(i),aligned);
    			}
    			else
    			{
    				//первая ячейка
    				SC.cell_draw_pix("signal_left",SC.get_color_sost(i),SC.get_color_background_sost(i));
    			}
    		}		
    		//добавляем созданный рисунок в ячейку отображения
    		SC.add_pix_to_cell();
    	}
    	//добавляем созданную ячейку в массив
    	SC.add_cell_to_array(x+column,y);
    }
    
    						
}

function square(param){
    //Квадрат
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x,y);
    SC.lineTo(x+w,y);
    SC.lineTo(x+w,y+w);
    SC.lineTo(x,y+w);
    SC.lineTo(x,y);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function str_down_left(param){
    //Стрелка направо-вниз
    //начальные координаты
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SOST = SC.get_count_color_sost();
    var COUNT_STR_SITE_SOST = SC.get_count_depends_count_sost();
    SC.create_cell();
    for(i=0;i<COUNT_STR_SOST;i++) 
    {
    	if(i<COUNT_STR_SITE_SOST) SC.cell_draw_pix("str_down_left_unknow",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else if((i>=COUNT_STR_SITE_SOST)&&(i<2*COUNT_STR_SITE_SOST)) SC.cell_draw_pix("str_down_left_plus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else SC.cell_draw_pix("str_down_left_minus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	SC.add_pix_to_cell()
    }
    SC.add_cell_to_array(x,y);
    
}

function str_down_left_minus(param){
    //стрелка вниз, влево, в минусовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(3*w/4,w/2,w,w/2);
    SC.draw_line(w/2,w,3*w/4,w/2);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function str_down_left_plus(param){
    //стрелка в плюсовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
    
}

function str_down_left_unknow(param){
    //стрелка вниз, влево, в неопределенном положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    SC.draw_line(w/2,w,3*w/4,w/2);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function str_down_right(param){
    //Стрелка направо-вниз
    //начальные координаты
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SOST = SC.get_count_color_sost();
    var COUNT_STR_SITE_SOST = SC.get_count_depends_count_sost();
    SC.create_cell();
    for(i=0;i<COUNT_STR_SOST;i++) 
    {
    	if(i<COUNT_STR_SITE_SOST) SC.cell_draw_pix("str_down_right_unknow",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else if((i>=COUNT_STR_SITE_SOST)&&(i<2*COUNT_STR_SITE_SOST)) SC.cell_draw_pix("str_down_right_plus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else SC.cell_draw_pix("str_down_right_minus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	SC.add_pix_to_cell()
    }
    SC.add_cell_to_array(x,y);
    
}

function str_down_right_minus(param){
    //стрелка вниз, вправо, в минусовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w/4,w/2);
    SC.draw_line(w/4,w/2,w/2,w);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function str_down_right_plus(param){
    //стрелка в плюсовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
    
}

function str_down_right_unknow(param){
    //стрелка вниз, вправо, в неопределенном положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    SC.draw_line(w/4,w/2,w/2,w);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function str_site_1ld(param){
    ﻿//Стрелочная секция с одной стрелкой направо-вниз
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,200);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(0,25,50,25);
    	SC.draw_line(75,50,50,100);
    	SC.draw_line(50,100,25,150);
    	SC.draw_line(25,150,12,175);
    	SC.draw_line(12,175,0,175);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,0,50,50)
    SC.add_cell_to_array(x-1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x-1,y+1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,100,50,50)
    SC.add_cell_to_array(x-1,y+2);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,150,50,50)
    SC.add_cell_to_array(x-1,y+3);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,50,50,50)
    SC.add_cell_to_array(x,y+1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,100,50,50)
    SC.add_cell_to_array(x,y+2);
    
    
    
    
    
}

function str_site_1ld_half(param){
    //Половина стрелочной секции с одной стрелкой налево-вниз
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,100);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(0,25,50,25);
    	SC.draw_line(75,50,50,100);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,0,50,50)
    SC.add_cell_to_array(x-1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x-1,y+1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,50,50,50)
    SC.add_cell_to_array(x,y+1);
    
}

function str_site_1lu(param){
    ﻿//Стрелочная секция с одной стрелкой направо-вниз
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,200);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(0,175,50,175);
    	SC.draw_line(75,150,50,100);
    	SC.draw_line(50,100,25,50);
    	SC.draw_line(25,50,12,25);
    	SC.draw_line(12,25,0,25);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,150,50,50)
    SC.add_cell_to_array(x-1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,100,50,50)
    SC.add_cell_to_array(x-1,y-1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x-1,y-2);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,0,50,50)
    SC.add_cell_to_array(x-1,y-3);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,100,50,50)
    SC.add_cell_to_array(x,y-1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,50,50,50)
    SC.add_cell_to_array(x,y-2);
    
    
    
    
    
}

function str_site_1lu_half(param){
    //Половина стрелочной секции с одной стрелкой направо-вниз
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,100);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(50,0,75,50);
    	SC.draw_line(0,75,50,75);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,0,50,50)
    SC.add_cell_to_array(x-1,y-1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x-1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,0,50,50)
    SC.add_cell_to_array(x,y-1);
    
}

function str_site_1rd(param){
    //Стрелочная секция с одной стрелкой направо-вниз
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,200);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(25,50,82,172);
    	SC.draw_line(85,175,100,175);
    	SC.draw_line(50,25,100,25);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x,y+1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,100,50,50)
    SC.add_cell_to_array(x,y+2);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,150,50,50)
    SC.add_cell_to_array(x,y+3);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,0,50,50)
    SC.add_cell_to_array(x+1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,50,50,50)
    SC.add_cell_to_array(x+1,y+1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,100,50,50)
    SC.add_cell_to_array(x+1,y+2);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,150,50,50)
    SC.add_cell_to_array(x+1,y+3);
    
    
}

function str_site_1rd_half(param){
    //Половина стрелочной секции с одной стрелкой направо-вниз
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,100);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(25,50,50,100);
    	SC.draw_line(50,25,100,25);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,0,50,50)
    SC.add_cell_to_array(x+1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x,y+1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,50,50,50)
    SC.add_cell_to_array(x+1,y+1);
    
}

function str_site_1ru(param){
    //Стрелочная секция с одной стрелкой направо-вверх
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,200);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(25,150,75,25);
    	SC.draw_line(75,25,100,25);
    	SC.draw_line(50,175,100,175);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,100,50,50)
    SC.add_cell_to_array(x,y-1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x,y-2);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,0,50,50)
    SC.add_cell_to_array(x,y-3);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,150,50,50)
    SC.add_cell_to_array(x+1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,100,50,50)
    SC.add_cell_to_array(x+1,y-1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,50,50,50)
    SC.add_cell_to_array(x+1,y-2);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,0,50,50)
    SC.add_cell_to_array(x+1,y-3);
    
    
}

function str_site_1ru_half(param){
    //Половина стрелочной секции с одной стрелкой направо-вверх
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(100,200);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(25,50,50,0);
    	SC.draw_line(50,75,100,75);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,0,50,50)
    SC.add_cell_to_array(x,y-1);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,0,50,50)
    SC.add_cell_to_array(x+1,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,50,50,50,50)
    SC.add_cell_to_array(x+1,y);
    
    
}

function str_site_1ru_up_half(param){
    //Верхняя половина стрелочной секции направо-вверх
    //начальные координаты
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SITE_SOST = SC.get_count_color_sost();
    for(i=0;i<COUNT_STR_SITE_SOST;i++)
    {
    	SC.create_pix(50,100);
    	SC.begin_painter();
    	SC.fill_rect(SC.get_color_background_sost(i));
    	SC.set_pen(SC.get_color_sost(i),9);
    	SC.draw_line(0,100,40,25);
    	SC.draw_line(40,25,50,25);
    	SC.push_back_pix_to_array()
    }
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,50,50,50)
    SC.add_cell_to_array(x,y);
    
    SC.create_cell();
    for(i=0;i<COUNT_STR_SITE_SOST;i++) SC.add_part_pix_to_cell(i,0,0,50,50)
    SC.add_cell_to_array(x,y-1);
    
}

function str_up_left(param){
    //Стрелка направо-вниз
    //начальные координаты
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SOST = SC.get_count_color_sost();
    var COUNT_STR_SITE_SOST = SC.get_count_depends_count_sost();
    SC.create_cell();
    for(i=0;i<COUNT_STR_SOST;i++) 
    {
    	if(i<COUNT_STR_SITE_SOST) SC.cell_draw_pix("str_up_left_unknow",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else if((i>=COUNT_STR_SITE_SOST)&&(i<2*COUNT_STR_SITE_SOST)) SC.cell_draw_pix("str_up_left_plus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else SC.cell_draw_pix("str_up_left_minus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	SC.add_pix_to_cell()
    }
    SC.add_cell_to_array(x,y);
    
}

function str_up_left_minus(param){
    //стрелка вверх, влево, в минусовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(3*w/4,w/2,w,w/2);
    SC.draw_line(w/2,0,3*w/4,w/2);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function str_up_left_plus(param){
    //стрелка в плюсовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function str_up_left_unknow(param){
    //стрелка вверх, влево, в неопределенном положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    SC.draw_line(w/2,0,3*w/4,w/2);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
}

function str_up_right(param){
    //Стрелка направо-вниз
    //начальные координаты
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var COUNT_STR_SOST = SC.get_count_color_sost();
    var COUNT_STR_SITE_SOST = SC.get_count_depends_count_sost();
    SC.create_cell();
    for(i=0;i<COUNT_STR_SOST;i++) 
    {
    	if(i<COUNT_STR_SITE_SOST) SC.cell_draw_pix("str_up_right_unknow",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else if((i>=COUNT_STR_SITE_SOST)&&(i<2*COUNT_STR_SITE_SOST)) SC.cell_draw_pix("str_up_right_plus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	else SC.cell_draw_pix("str_up_right_minus",SC.get_color_sost(i),SC.get_color_background_sost(i));
    	SC.add_pix_to_cell()
    }
    SC.add_cell_to_array(x,y);
    
}

function str_up_right_minus(param){
    //стрелка вверх, вправо, в минусовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w/4,w/2);
    SC.draw_line(w/4,w/2,w/2,0);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
}

function str_up_right_plus(param){
    //стрелка в плюсовом положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function str_up_right_unknow(param){
    //стрелка вверх, вправо, в неопределенном положении
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6+1);
    SC.draw_line(0,w/2,w,w/2);
    SC.draw_line(w/4,w/2,w/2,0);
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
}

function track(param){
    //количество состояний и соответствующих им цветов отображения
    var COUNT_TRACK_SOST = SC.get_count_color_sost();
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var len  = SC.get_int_attr("len");
    var j = (len-SC.get_pix_count_cells(0))/2;
    //проход по координатам х
    for(column=0;column<len;column++)
    {
    	//создаем ячейку отображения
    	SC.create_cell();
    	//проход по возможным состояниям отображения пути
    	for(i=0;i<COUNT_TRACK_SOST;i++)
    	{				
    		//если выводить надпись (последний параметр 132=Qt::AlignCenter)
    		if(column==j) SC.cell_draw_text(j-(len-SC.get_pix_count_cells(0))/2,SC.get_color_sost(i),SC.get_color_background_sost(i),132);
    		//если выводить треугольник в первой позиции
    		else if ((column==0)&&(i==3)) SC.cell_draw_pix("triangle_left",SC.get_color_sost(i),SC.get_color_background_sost(i));
    		//если выводить треугольник в последней ячейки
    		else if ((column==len-1)&&(i==4)) SC.cell_draw_pix("triangle_right",SC.get_color_sost(i),SC.get_color_background_sost(i));
    		//если выводить линию
    		else SC.cell_draw_pix("cell_one_line",SC.get_color_sost(i),SC.get_color_background_sost(i));
    		//добавляем созданный рисунок в ячейку отображения
    		SC.add_pix_to_cell();
    		
    	}
    	//изменяем координату отображения следующей ячейки надписи
    	if ((column==j)&&(j<(len+SC.get_pix_count_cells(0))/2-1)) j++;
    	//добавляем созданную ячейку в массив
    	SC.add_cell_to_array(x+column,y);
    }
    
    
}

function track_ab(param){
    //блок-участок автоблокировки
    var COUNT_TRACK_SOST = SC.get_count_color_sost();
    //начальные координаты
    var x = SC.get_int_attr("x");
    var yn = SC.get_int_attr("yn");
    //конечные координаты
    var yf = SC.get_int_attr("yf");
    
    for(y=yn;y<yf;y++)
    {
    	SC.create_cell();
    	//проход по возможным состояниям отображения пути
    	for(i=0;i<COUNT_TRACK_SOST;i++)
    	{				
    	 	SC.cell_draw_pix("cell_one_line_vert",SC.get_color_sost(i),SC.get_color_background_sost(i));			
    		SC.add_pix_to_cell();
    	}
    	SC.add_cell_to_array(x,y);
    }
    
}

function track_site(param){
    //количество состояний и соответствующих им цветов отображения
    var COUNT_TRACK_SOST = SC.get_count_color_sost();
    //начальные координаты и длинна 
    var x = SC.get_int_attr("x");
    var y = SC.get_int_attr("y"); 
    var len  = SC.get_int_attr("len");
    for(column=0;column<len;column++)
    {
    	SC.create_cell();
    	for(i=0;i<COUNT_TRACK_SOST;i++)
    	{			
    		SC.cell_draw_pix("cell_one_line",SC.get_color_sost(i),SC.get_color_background_sost(i));			
    		SC.add_pix_to_cell();
    		
    	}
    	SC.add_cell_to_array(x+column,y);
    }
    
    
}

function triangle(param){
    //Треугольник в правую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x+w/2,y+w/2);
    SC.lineTo(x+w/2,y+w/2);
    SC.lineTo(x+w/2,y+w/2);
    SC.lineTo(x+w/2,y+w/2);
    SC.fillPath();
    SC.closePath();
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
}

function triangle_down(param){
    //Треугольник в левую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x+w/4,y+w/4);
    SC.lineTo(x+3*w/4,y+w/4);
    SC.lineTo(x+w/2,y+3*w/4);
    SC.lineTo(x+w/4,y+w/4);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
}

function triangle_left(param){
    //Треугольник в левую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x+w/4,y+w/2);
    SC.lineTo(x+3*w/4,y+w/4);
    SC.lineTo(x+3*w/4,y+3*w/4);
    SC.lineTo(x+w/4,y+w/2);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function triangle_left_half(param){
    //Треугольник в левую сторону на половину клетки (с середины клетки)
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x+w/2,y+w/2);
    SC.lineTo(x+w,y);
    SC.lineTo(x+w,y+w);
    SC.lineTo(x+w/2,y+w/2);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function triangle_left_half_left(param){
    //Треугольник в левую сторону на половину клетки (с начала клетки)
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x,y+w/2);
    SC.lineTo(x+w/2,y);
    SC.lineTo(x+w,y);
    SC.lineTo(x+w,y+w);
    SC.lineTo(x+w/2,y+w);
    SC.lineTo(x,y+w/2);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function triangle_right(param){
    //Треугольник в правую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x+w/4,y+w/4);
    SC.lineTo(x+3*w/4,y+w/2);
    SC.lineTo(x+w/4,y+3*w/4);
    SC.lineTo(x+w/4,y+w/4);
    SC.fillPath();
    SC.closePath();
    
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
}

function triangle_rigth_half(param){
    //Треугольник в левую сторону на половину клетки (с начала клетки)
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x,y);
    SC.lineTo(x+w/2,y+w/2);
    SC.lineTo(x,y+w);
    SC.lineTo(x,y);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function triangle_rigth_half_rigth(param){
    //Треугольник в левую сторону на половину клетки (с начала клетки)
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x,y);
    SC.lineTo(x+w/2,y);
    SC.lineTo(x+w,y+w/2);
    SC.lineTo(x+w/2,y+w);
    SC.lineTo(x,y+w);
    SC.lineTo(x,y);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
    
    
    
}

function triangle_up(param){
    //Треугольник в левую сторону
    var x = SC.rect_x();
    var y = SC.rect_y();
    var w = SC.rect_w();
    SC.set_pen(SC.curr_color_name, w/6);
    SC.beginPath();
    SC.moveTo(x+w/4,y+3*w/4);
    SC.lineTo(x+3*w/4,y+3*w/4);
    SC.lineTo(x+w/2,y+w/4);
    SC.lineTo(x+w/4,y+3*w/4);
    SC.fillPath();
    SC.closePath();
    //устанавливаем флаг возможности 
    //внесения в коллекцию отрисованной картинки
    SC.set_pixmap_collection();
}

