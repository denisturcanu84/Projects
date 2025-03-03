#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_CENTER 76
#define WM_LBUTTONDOWN 513

using namespace std;
int stanga, sus, width, height, latura, m = 1, l = 1, c = 1, ul, uc, pr, jucator = 0, p, afaratablei = 0;
int v[65];
int matrice[11][11];
bool gata;
int text_color = 10;

void primapiesa(int x, int y, int m) {
        int width, latura;
        width = 540;
        latura = width / m;
        setcolor(WHITE);
        line((100 + latura / 2) * x, 50 * y, (100 + latura / 2) * x, 50 * y + latura);
        line(100 * x, (50 + latura / 2) * y, 100 * x + latura, (50 + latura / 2) * y);
}

void coltnegru(int m) {
        int width, latura;
        setcolor(text_color);
        setfillstyle(SOLID_FILL, text_color);
        width = 540;
        latura = width / m;
        bar(100 + (m - 1) * latura, 50 + (m - 1) * latura, 100 + m * latura, 50 + m * latura);
}

void pozitiecoltnegru(int m) {
        coltnegru(m);
        primapiesa(1, 1, m);
}

void desen(int numar) {
        int i, j;
        width = 540;
        height = 540;
        latura = width / numar;
        sus = 50;
        stanga = 100;
        for (i = 1; i <= numar; i++)
                for (j = 1; j <= numar; j++)
                        rectangle(stanga + latura * (i - 1), sus + latura * (j - 1), stanga + latura * i, sus + latura * j);
}

void piesa(int i) {
        rectangle(800, 162 + i * 112, 890, 252 + i * 112);
}

void piesa1() {
        rectangle(800, 162, 890, 252);
        line(845, 162, 845, 252);
        line(800, 209, 890, 209);
}

void piesa2() {
        int stangle = 270, endangle = 0, radius = 45;
        rectangle(800, 274, 890, 364);
        arc(800, 274, stangle, endangle, radius);
        stangle = 90, endangle = 180;
        arc(890, 364, stangle, endangle, radius);
}

void piesa3() {
        int stangle = 0, endangle = 90, radius = 45;
        rectangle(800, 386, 890, 476);
        arc(800, 476, stangle, endangle, radius);
        stangle = 180, endangle = 270;
        arc(890, 386, stangle, endangle, radius);
}

void optiune1(int xm, int ym) {
        int width, latura;
        width = 540;
        latura = width / m;
        line(xm, ym - latura / 2, xm, ym + latura / 2);
        line(xm - latura / 2, ym, xm + latura / 2, ym);
}

void optiune2(int xm, int ym) {
        int stangle = 270, endangle = 0, radius = latura / 2;
        arc(xm - latura / 2, ym - latura / 2, stangle, endangle, radius);
        stangle = 90, endangle = 180;
        arc(xm + latura / 2, ym + latura / 2, stangle, endangle, radius);
}

void optiune3(int xm, int ym) {
        int stangle = 0, endangle = 90, radius = latura / 2;
        arc(xm - latura / 2, ym + latura / 2, stangle, endangle, radius);
        stangle = 180, endangle = 270;
        arc(xm + latura / 2, ym - latura / 2, stangle, endangle, radius);
}

int alegePiesa(int & z) {
        int i = 1;
        char c;
        piesa1();
        piesa2();
        piesa3();
        setcolor(RED);
        piesa(z);
        do {
                c = (char) getch();
                switch (c) {
                case KEY_UP: {
                        setcolor(WHITE);
                        piesa(z);
                        if (z == 0) z = 2;
                        else z--;
                        setcolor(RED);
                        piesa(z);
                }
                break;
                case KEY_DOWN: {
                        setcolor(WHITE);
                        piesa(z);
                        if (z == 2) z = 0;
                        else z++;
                        setcolor(RED);
                        piesa(z);
                }
                break;
                }
        } while (!(GetAsyncKeyState(VK_RETURN) & 0x8000));

        setcolor(WHITE);
        i = 0;
        return i;
}

bool punerePiesa() {
        int linia, coloana, x, y, k = 0;
        int x1, y1, x2, y2;
        int xmijloc, ymijloc;
        bool ok = false;
        if (ismouseclick(WM_LBUTTONDOWN)) {
                clearmouseclick(WM_LBUTTONDOWN);
                x = mousex();
                y = mousey();
                if (x >= stanga && x <= stanga + width && y >= sus && y <= sus + height) {
                        linia = (y - sus) / latura + 1;
                        coloana = (x - stanga) / latura + 1;
                        if (v[matrice[linia][coloana]] == 1) {
                                jucator = abs(1 - jucator);
                                if (jucator == 0)
                                        outtextxy(910, 80, "Randul jucatorului 1");
                                else if (jucator == 1)
                                        outtextxy(910, 80, "Randul jucatorului 2");

                                v[matrice[linia][coloana]] = 1 + p;
                                x1 = stanga + latura * (coloana - 1);
                                y1 = sus + latura * (linia - 1);
                                x2 = x1 + latura;
                                y2 = y1 + latura;
                                xmijloc = (x1 + x2) / 2;
                                ymijloc = (y1 + y2) / 2;
                                if (p == 1) {
                                        optiune1(xmijloc, ymijloc);
                                        ok = true;
                                        if (l == linia && c < coloana) {
                                                if (matrice[l][coloana + 1] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[l][coloana + 1] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[l][coloana + 1]] == 0) {
                                                                v[matrice[l][coloana + 1]] = 1;
                                                                c = c + 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                c = c + 1;
                                                                while (ok == 0) {

                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                } else if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                } else if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }

                                        } else if (l == linia && c > coloana) {
                                                if (matrice[l][coloana - 1] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[l][coloana - 1] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[l][coloana - 1]] == 0) {
                                                                v[matrice[l][coloana - 1]] = 1;
                                                                c = c - 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                c = c - 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l > linia && c == coloana) {
                                                if (matrice[linia - 1][c] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[linia - 1][c] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[linia - 1][c]] == 0) {
                                                                v[matrice[linia - 1][c]] = 1;
                                                                l = l - 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                l = l - 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l < linia && c == coloana) {
                                                if (matrice[linia + 1][c] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[linia + 1][c] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[linia + 1][c]] == 0) {
                                                                v[matrice[linia + 1][c]] = 1;
                                                                l = l + 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                l = l + 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                } else if (p == 2) {
                                        optiune2(xmijloc, ymijloc);
                                        ok = true;
                                        if (l == linia && c < coloana) {
                                                if (matrice[l - 1][coloana] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[l - 1][coloana] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[l - 1][coloana]] == 0) {
                                                                v[matrice[l - 1][coloana]] = 1;
                                                                c = c + 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                c = c + 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l == linia && c > coloana) {
                                                if (matrice[l + 1][coloana] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[l + 1][coloana] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[l + 1][coloana]] == 0) {
                                                                v[matrice[l + 1][coloana]] = 1;
                                                                c = c - 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                c = c - 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l > linia && c == coloana) {
                                                if (matrice[linia][c + 1] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[linia][c + 1] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[linia][c + 1]] == 0) {
                                                                v[matrice[linia][c + 1]] = 1;
                                                                l = l - 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                l = l - 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l < linia && c == coloana) {
                                                if (matrice[linia][c - 1] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[linia][c - 1] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[linia][c - 1]] == 0) {
                                                                v[matrice[linia][c - 1]] = 1;
                                                                l = l + 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                l = l + 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                } else {
                                        optiune3(xmijloc, ymijloc);
                                        ok = true;
                                        if (l == linia && c < coloana) {
                                                if (matrice[l + 1][coloana] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[l + 1][coloana] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[l + 1][coloana]] == 0) {
                                                                v[matrice[l + 1][coloana]] = 1;
                                                                c = c + 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                c = c + 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l == linia && c > coloana) {
                                                if (matrice[l - 1][coloana] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[l - 1][coloana] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[l - 1][coloana]] == 0) {
                                                                v[matrice[l - 1][coloana]] = 1;
                                                                c = c - 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                c = c - 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l > linia && c == coloana) {
                                                if (matrice[linia][c - 1] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[linia][c - 1] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[linia][c - 1]] == 0) {
                                                                v[matrice[linia][c - 1]] = 1;
                                                                l = l - 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                l = l - 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (l < linia && c == coloana) {
                                                if (matrice[linia][c + 1] == 0) {
                                                        afaratablei = 1;
                                                        gata = true;
                                                } else if (matrice[linia][c + 1] == m * m) gata = true;
                                                else {
                                                        if (v[matrice[linia][c + 1]] == 0) {
                                                                v[matrice[linia][c + 1]] = 1;
                                                                l = l + 1;
                                                        } else {
                                                                int ok;
                                                                ok = 0;
                                                                uc = c;
                                                                ul = l;
                                                                l = l + 1;
                                                                while (ok == 0) {
                                                                        if (matrice[l][c] == 0) {
                                                                                afaratablei = 1;
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (matrice[l][c] == m * m) {
                                                                                gata = true;
                                                                                ok = 1;
                                                                        } else if (v[matrice[l][c]] == 0) {
                                                                                v[matrice[l][c]] = 1;
                                                                                l = ul;
                                                                                c = uc;
                                                                                ok = 1;
                                                                        } else {
                                                                                pr = v[matrice[l][c]] - 1;
                                                                                if (pr == 1) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 2) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        }
                                                                                }
                                                                                if (pr == 3) {
                                                                                        if (ul == l && uc < c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l + 1;
                                                                                        } else if (ul == l && uc > c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                l = l - 1;
                                                                                        } else if (ul > l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c - 1;
                                                                                        } else if (ul < l && uc == c) {
                                                                                                uc = c;
                                                                                                ul = l;
                                                                                                c = c + 1;
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }

                        }
                }
                //clearmouseclick(WM_LBUTTONDOWN);
        }
        return ok;
}
bool punereultimaPiesa() {
        int linia, coloana, x, y;
        int x1, y1, x2, y2;
        int xmijloc, ymijloc;
        bool ok = false;
        if (ismouseclick(WM_LBUTTONDOWN)) {
                clearmouseclick(WM_LBUTTONDOWN);
                x = mousex();
                y = mousey();
                if (x >= stanga && x <= stanga + width && y >= sus && y <= sus + height) {
                        linia = (y - sus) / latura + 1;
                        coloana = (x - stanga) / latura + 1;
                        if (matrice[linia][coloana] == m * m) {
                                jucator = abs(1 - jucator);
                                if (jucator == 0) outtextxy(910, 80, "Randul jucatorului 1");
                                else if (jucator == 1) outtextxy(910, 80, "Randul jucatorului 2");

                                x1 = stanga + latura * (coloana - 1);
                                y1 = sus + latura * (linia - 1);
                                x2 = x1 + latura;
                                y2 = y1 + latura;
                                xmijloc = (x1 + x2) / 2;
                                ymijloc = (y1 + y2) / 2;
                                if (p == 1) {
                                        optiune1(xmijloc, ymijloc);
                                        ok = true;
                                } else if (p == 2) {
                                        optiune2(xmijloc, ymijloc);
                                        ok = true;
                                } else if (p == 3) {
                                        optiune3(xmijloc, ymijloc);
                                        ok = true;
                                }
                        }
                }
        }
}

int start() {
        int i, j, n, x = 1, z, nr = 0;
        n = m + 2;
        for (j = 0; j <= n - 1; j++) {
                matrice[0][j] = 0;
                matrice[n - 1][j] = 0;
        }
        for (i = 0; i <= n - 1; i++) {
                matrice[i][0] = 0;
                matrice[i][n - 1] = 0;
        }

        for (i = 1; i <= m; i++)
                for (j = 1; j <= m; j++) {
                        matrice[i][j] = x;
                        x = x + 1;
                }
        v[1] = 2;
        v[2] = v[m + 1] = 1;

        initwindow(1200, 700, "COLTUL NEGRU", 150, 50);
        desen(m);
        pozitiecoltnegru(m);
        gata = false;
        outtextxy(910, 80, "Randul jucatorului 1");
        bool ok;
        do {
                z = 0;
                i = 1;
                do {
                        i = alegePiesa(z);

                } while (i == 1);
                p = z;
                p++;
                do {
                        ok = punerePiesa();
                } while (!ok);
                nr++;
        } while (nr == 0);

        if (v[2] > 1) {
                v[m + 1] = 0;
        } else if (v[m + 1] > 1) {
                v[2] = 0;
        }

        if (gata == false)
                do {
                        z = 0;
                        i = 1;
                        do {
                                i = alegePiesa(z);

                        } while (i == 1);
                        p = z;
                        p++;
                        do {
                                ok = punerePiesa();
                        } while (!ok);

                } while (!gata);

        if (afaratablei == 1) {
                outtextxy(910, 120, "JOC TERMINAT");
                if (jucator == 1) {
                        setcolor(text_color);
                        settextstyle(BOLD_FONT, HORIZ_DIR, 1);
                        outtextxy(910, 140, "Castigator: Jucatorul 2");
                } else if (jucator == 0) {
                        setcolor(text_color);
                        settextstyle(BOLD_FONT, HORIZ_DIR, 1);
                        outtextxy(910, 140, "Castigator: Jucatorul 1");
                }
        } else {
                nr = 0;
                do {
                        z = 0;
                        i = 1;
                        do {
                                i = alegePiesa(z);
                        } while (i == 1);
                        p = z;
                        p++;
                        do {
                                ok = punereultimaPiesa();
                        } while (!ok);
                        nr++;
                } while (nr == 0);

                outtextxy(910, 120, "JOC TERMINAT");
                if (jucator == 1) {
                        setcolor(text_color);
                        settextstyle(BOLD_FONT, HORIZ_DIR, 1);
                        outtextxy(910, 140, "Castigator: Jucatorul 1");
                } else if (jucator == 0) {
                        setcolor(text_color);
                        settextstyle(BOLD_FONT, HORIZ_DIR, 1);
                        outtextxy(910, 140, "Castigator: Jucatorul 2");
                }
        }

        getch();
        closegraph();

        return 0;
}

void menu(int text_color) {
        settextstyle(BOLD_FONT, HORIZ_DIR, 8);
        setcolor(text_color);
        outtextxy(330, 100, "COLTUL NEGRU");

        setcolor(text_color);
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(330, 250, "1.");
        outtextxy(330, 300, "2.");
        outtextxy(330, 350, "3.");
        setcolor(WHITE);
        outtextxy(380, 250, "PLAY");
        outtextxy(380, 300, "INSTRUCTIUNI");
        outtextxy(380, 350, "EXIT");

}
void instructiuni(int text_color) {

        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        setcolor(text_color);
        outtextxy(30, 30, "REGULI 'COLTUL NEGRU'");

        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        setcolor(WHITE);
        outtextxy(30, 90, "Trebuie creat un drum continuu ce leaga prima piesa de pe tabla de coltul colorat.");
        outtextxy(30, 120, "Jucatorul care termina drumul pe coltul colorat este castigator.");
        outtextxy(30, 150, "Jucatorul care duce drumul in afara tablei pierde.");
        outtextxy(30, 180, "Este obligatoriu ca fiecare jucator sa continue drumul.");

        setcolor(text_color);
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(30, 270, "INSTRUCTIUNI");

        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        setcolor(WHITE);
        outtextxy(30, 330, "Apasa sageata SUS/JOS pentru a alege piesa dorita si ENTER pentru a o selecta.");
        outtextxy(30, 360, "Click mouse stanga pe locul posibil pentru a aseza piesa.");

        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        setcolor(text_color);
        outtextxy(20, 520, "1.PLAY");
        outtextxy(20, 550, "3.EXIT");

}
void marimejocvisual() {
        setcolor(text_color);
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(30, 30, "ALEGE MARIMEA TABLEI DE JOC:");

        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        outtextxy(30, 140, "A.");
        outtextxy(30, 170, "B.");
        outtextxy(30, 200, "C.");
        outtextxy(30, 230, "D.");
        outtextxy(30, 260, "E.");

        setcolor(WHITE);
        outtextxy(70, 140, "4x4");
        outtextxy(70, 170, "5x5");
        outtextxy(70, 200, "6x6");
        outtextxy(70, 230, "7x7");
        outtextxy(70, 260, "8x8");
        setcolor(text_color);
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        outtextxy(20, 520, "2.INSTRUCTIUNI");
        outtextxy(20, 550, "3.EXIT");
}
void marimejoc() {
        if (GetAsyncKeyState('A') & 0x8000)
                m = 4;
        else if (GetAsyncKeyState('B') & 0x8000)
                m = 5;
        else if (GetAsyncKeyState('C') & 0x8000)
                m = 6;
        else if (GetAsyncKeyState('D') & 0x8000)
                m = 7;
        else if (GetAsyncKeyState('E') & 0x8000)
                m = 8;
}
int main() {
        initwindow(1200, 600, "COLTUL NEGRU", 150, 50);
        menu(text_color);
        int pg = 1;
        int fl = 0;
        while (1) {
                setactivepage(pg);
                setvisualpage(1 - pg);

                if (fl == 0) {

                        if (!GetAsyncKeyState(0x31)) {
                                cleardevice();
                                menu(text_color);
                        }

                        fl++;
                }

                if (GetAsyncKeyState(0x31)) {
                        cleardevice();
                        getch();
                        marimejocvisual();
                        marimejoc();
                        if (m != 1) {
                                closegraph();
                                start();
                        }
                }

                if (GetAsyncKeyState(0x32)) {
                        cleardevice();
                        instructiuni(text_color);
                }

                if (GetAsyncKeyState(0x33)) {
                        cleardevice();
                        closegraph();
                        return 0;
                }
                pg = 1 - pg;
                delay(10);

        }
        getch();
        closegraph();
}
