cmake_minimum_required(VERSION 4.1)
project(INF155_TP1_NumberMatch_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code)

add_executable(INF155_TP1_NumberMatch_code
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/affichages.cpp
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/affichages.h
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/gestion_jeu.cpp
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/gestion_jeu.h
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/grille_chiffres.cpp
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/grille_chiffres.h
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/liste_couples.cpp
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/liste_couples.h
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/Main_jeu.cpp
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/utilitaires.cpp
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/utilitaires.h
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/WinConsole.cpp
        INF155_TP1_NumberMatch_code/INF155_TP1_NumberMatch_code/WinConsole.h)
