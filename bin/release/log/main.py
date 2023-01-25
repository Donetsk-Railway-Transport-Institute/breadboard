# -*- coding: utf-8 -*-
__author__ = 'Чепцов М.Н.'

from datetime import datetime
import breadboard_lib as b_l
import matplotlib.pyplot as plt
import sys

if __name__ == "__main__":
    data = b_l.load_log_file('19.01.23.log')
    if data==None: 
        print("Data is not found for this options")
        sys.exit(1)

    g_l = b_l.get_obj_states(u"Горная-Луговая:2П",data)
    for g in g_l: print(g)
