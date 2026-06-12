#include "wordcloud.hpp"

#include <QByteArray>
#include <QFont>
#include <QFontMetrics>
#include <QGuiApplication>
#include <QImage>
#include <QPainter>
#include <QString>
#include <cctype>
#include <iostream>

using namespace std;

int W = 1600;
int H = 1000;

string aa(string x) {
    string r = "";
    for (int i = 0; i < (int)x.size(); i++) {
        char c = x[i];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            r += (char)tolower((unsigned char)c);
        }
    }
    return r;
}

vector<ww> bb(vector<string> x) {
    vector<ww> a;
    for (int i = 0; i < (int)x.size(); i++) {
        string t = aa(x[i]);
        if (t == "") {
            continue;
        }

        int k = -1;
        for (int j = 0; j < (int)a.size(); j++) {
            if (a[j].s == t) {
                k = j;
            }
        }

        if (k == -1) {
            ww q;
            q.s = t;
            q.n = 1;
            a.push_back(q);
        } else {
            a[k].n = a[k].n + 1;
        }
    }

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)a.size() - 1; j++) {
            if (a[j].n < a[j + 1].n) {
                ww z = a[j];
                a[j] = a[j + 1];
                a[j + 1] = z;
            }
        }
    }
    return a;
}

bool dd(vector<string> x, string f) {
    vector<ww> a = bb(x);
    QImage img(W, H, QImage::Format_RGB32);
    img.fill(Qt::white);

    QPainter p(&img);
    int maxx = 1000;
    int now = 0;
    int hi = 0;
    int yy = 280;

    int i = 0;
    while (i < (int)a.size()) {
        int j = i;
        now = 0;
        hi = 0;

        while (j < (int)a.size()) {
            int fs = 16 + a[j].n * 9;
            if (fs > 72) fs = 72;
            QFont ff("Arial", fs);
            QFontMetrics mm(ff);
            QString q = QString::fromStdString(a[j].s);
            int len = mm.horizontalAdvance(q) + 14;
            int hh = mm.height() + 4;

            if (now + len > maxx && now > 0) {
                break;
            }

            now = now + len;
            if (hh > hi) hi = hh;
            j++;
        }

        int xx = W / 2 - now / 2;
        for (int k = i; k < j; k++) {
            int fs = 16 + a[k].n * 9;
            if (fs > 72) fs = 72;
            QFont ff("Arial", fs);
            QFontMetrics mm(ff);
            p.setFont(ff);
            p.setPen(QColor(40 + k * 55 % 170, 50 + k * 35 % 150, 70 + k * 20 % 130));

            QString q = QString::fromStdString(a[k].s);
            p.drawText(xx, yy + hi / 2 + mm.ascent() / 2, q);
            xx = xx + mm.horizontalAdvance(q) + 14;
        }

        yy = yy + hi + 2;
        i = j;
    }

    p.end();
    return img.save(QString::fromStdString(f), "JPG");
}

#ifndef WORDCLOUD_TESTS
int main(int argc, char *argv[]) {
    if (qEnvironmentVariableIsEmpty("QT_QPA_PLATFORM")) {
        qputenv("QT_QPA_PLATFORM", QByteArray("offscreen"));
    }

    QGuiApplication app(argc, argv);

    if (argc < 2) {
        cout << "words pls\n";
        return 1;
    }

    vector<string> v;
    for (int i = 1; i < argc; i++) {
        v.push_back(argv[i]);
    }

    if (!dd(v, "wordcloud.jpg")) {
        cout << "bad save\n";
        return 2;
    }

    cout << "ok wordcloud.jpg\n";
    return 0;
}
#endif
