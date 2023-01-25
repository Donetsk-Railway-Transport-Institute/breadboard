# -*- coding: utf-8 -*-
__author__ = 'Чепцов М.Н.'

import numpy as np
from datetime import datetime
import codecs

#Чтение лог файла с именем filename. Функция возвращает массив data, 
#каждая строка которого состоит из трех записей:
#    0 - время операции
#    1 - наименование объекта и состояние (напр. Горная:1П:1)
#    2 - расшифровка объекта и его состояния
def load_log_file(filename):
    data = []
    with codecs.open(filename, "r", 'UTF-8') as file:
        for line in file:
            if not "set_sost_to_log" in line: continue
            converters = [datetime.strptime(line.split("[")[1].split("]")[0], "%d.%m.%y %H:%M:%S"), 
                         line.split("(")[1].split(")")[0],
                         line.split("#")[1]]
            data.append(converters)
    return data

#Функция возвращает все данные по объекту obj_name из массива data
def get_obj_states(obj_name, data):
    arr = []
    for d in data:
        if str(d[1]).find(obj_name)>=0:
            curr_data = [d[1].split(":")[2], 
                         d[1].split(":")[0]+":"+d[1].split(":")[1], 
                         d[0], d[2]]
            arr.append(curr_data)
    return arr
