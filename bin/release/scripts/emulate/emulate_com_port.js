function write(data)
{
    var result = data;
    if(data=="0f 01 01 00 00 00 03 04 1F") result = "0f 01 01 00 00 00 3A 31 74";
    if(data=="0f 01 01 00 00 00 02 03 4C") result = "0f 01 01 00 00 00 2A 24 44";
    if(data=="0f 01 01 00 00 00 04 04 F2") result = "0f 01 01 00 00 00 4A 3E A4";
    if(data=="0f 03 01 00 00 00 01 04 1F") result = "0f 03 01 00 00 00 1A 18 BA";
    if(data=="0f 01 01 00 00 00 01 02 79") result = "0f 01 01 00 00 00 1A 17 14";
    if(data=="0f 04 01 00 00 00 02 05 C5") result = "0f 04 01 00 00 00 2A 26 BD";
    if(data=="0f 04 01 00 00 00 03 06 98") result = "0f 04 01 00 00 00 3A 33 ED";
    if(data=="0f 02 01 00 00 00 01 03 4C") result = "0f 02 01 00 00 00 1A 17 E7";
    if(data=="0f 04 01 00 00 00 01 04 F2") result = "0f 04 01 00 00 00 1A 19 8D";
    if(data=="0f 03 01 00 00 00 02 04 F2") result = "0f 03 01 00 00 00 2A 25 EA";
    if(data=="0f 03 01 00 00 00 04 06 98") result = "0f 03 01 00 00 00 4A 40 4A";
    if(data=="0f 03 01 00 00 00 03 05 C5") result = "0f 03 01 00 00 00 3A 33 1A";
    if(data=="0f 02 01 00 00 00 03 04 F2") result = "0f 02 01 00 00 00 3A 32 47";
    if(data=="0f 02 01 00 00 00 04 05 C5") result = "0f 02 01 00 00 00 4A 3F 77";
    if(data=="0f 02 01 00 00 00 02 04 1F") result = "0f 02 01 00 00 00 2A 25 17";
//    if((data=="01 05 F0")&&(C.get_count()<75)) result = "01 05 8F F0";
//    if((data=="0f 01 01 00 00 00 03 04 1F")&&(C.get_count()>75))  result = "0f 01 8F 00 00 00 04 79 FC";
//    if((data=="0f 01 01 00 00 00 03 04 1F")&&(C.get_count()>95))  result = "0f 01 8F 00 00 00 03 79 29";

//  <obj_command msg="Горная:1:2" code="03 05 00 00 00 58 4F 20" comment="перевод стрелки 1 в - ст. Горная"/>
    
    C.set_e_data(result);
//    if(data==result) C.msg_to_log("function write("+data+") = "+result);
}
