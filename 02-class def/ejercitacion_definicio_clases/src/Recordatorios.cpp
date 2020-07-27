#include <iostream>
#include <list>
#include <vector>
#include<map>


using namespace std;

using uint = unsigned int;


// Pre: 0 < mes <= 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(int m, int d);
    int mes() const;
    int dia() const;
    #if EJ >= 9 // Para ejercicio 9
    bool operator==(const Fecha& o) const;
    #endif
    bool operator<(const Fecha& o) const;
    void incrementar_dia();

  private:
    int mes_;
    int dia_;
};

Fecha::Fecha(int m, int d) : mes_(m), dia_(d) {}

int Fecha::mes() const{
    return mes_;
}

int Fecha::dia() const{
    return dia_;
}

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/" << f.mes();
}

#if EJ >= 9
bool Fecha::operator==(const Fecha &o) const {
    bool igual_dia = this->dia() == o.dia();
    bool igual_mes = this->mes() == o.mes();
    return igual_dia && igual_mes;
}
#endif

bool Fecha::operator<( const Fecha &o) const {
    bool res = false;
    if(this -> mes() < o.mes()){
        res = true;
    }else{
        if(this -> mes() == o.mes()){
            res = this -> dia() < o.dia();
        }else{
            res = false;
        }
    }
    return res;
}

void Fecha::incrementar_dia() {
    if(dias_en_mes(this->mes()) == 30){
        if(this->dia_ == 30){
            this->dia_ = 1;
            this->mes_ += 1;
        }else{
            this->dia_ += 1;
        }
    }else{
        if(dias_en_mes(this->mes_) == 31){
            if(this->mes_ == 12){
                if(this->dia_ == 31){
                    this->dia_ = 1;
                    this->mes_ = 1;
                }else{
                    this->dia_ += 1;
                }
            }else{
                if(this->dia_ == 31){
                    this->dia_ = 1;
                    this->mes_ += 1;
                }else{
                    this->dia_ += 1;
                }
            }
        }else{
            if(this->dia_ == 28){
                this->dia_ = 1;
                this->mes_ += 1;
            }else{
                this->dia_ += 1;
            }
        }
    }
}

// Ejercicio 11, 12

class Horario{
    public:
        Horario(uint hora, uint min);
        uint hora();
        uint min();
        bool operator<(Horario h);

    private:
        uint hora_;
        uint min_;
};

Horario::Horario(uint h, uint m) : hora_(h), min_(m) {}

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}

bool Horario::operator<(Horario h) {
    if(this->hora() < h.hora()){
        return true;
    }else{
        if(this->hora() == h.hora()){
            return this->min() < h.min();
        }else{
            return false;
        }
    }
}

ostream& operator<<(ostream& os, Horario h) {
    os << h.hora() << ":" << h.min();
    return os;
}

// Ejercicio 13

class Recordatorio{
    public:
        Recordatorio(Fecha f, Horario , string msj);
        string msj();
        Fecha f();
        Horario h();

    private:
        string msj_;
        Fecha f_;
        Horario h_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, string m) : msj_(m), f_(f), h_(h) {}

string Recordatorio::msj() {
    return msj_;
}

Fecha Recordatorio::f() {
    return f_;
}

Horario Recordatorio::h() {
    return h_;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.msj() << " @ " << r.f() << " " << r.h();
}

// Ejercicio 14

class Agenda {
    public:
        Agenda(Fecha fecha_inicial);
        void agregar_recordatorio(Recordatorio rec);
        void incrementar_dia();
        vector<Recordatorio> recordatorios_de_hoy();
        Fecha hoy();
    private:
        map<Fecha, vector<Recordatorio>> agenda_;
        Fecha hoy_;
};

Agenda::Agenda(Fecha f_i) : hoy_(f_i) {}

Fecha Agenda::hoy() {
    return hoy_;
}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    agenda_[rec.f()].push_back(rec);
}

void Agenda::incrementar_dia() {
    this-> hoy_.incrementar_dia();
}

vector<Recordatorio> Agenda::recordatorios_de_hoy() {
    vector<Recordatorio> recordatorios;
    for(int i = 0; i < agenda_[hoy_].size(); i++){
        recordatorios.push_back(agenda_[hoy_][i]);
    }
    vector<Recordatorio> res;
    for(int i = 0; i < recordatorios.size() - 1; i++) {
        Recordatorio min = recordatorios[i];
        Horario primero = recordatorios[i].h();
        for(int j = i+1; j < recordatorios.size(); j++){
            if(recordatorios[j].h() < primero){
                min = recordatorios[j];
                primero = recordatorios[j].h();
            }
        }
        res.push_back(min);
    }
    return res;
}


ostream& operator<<(ostream& os, Agenda a) {
    vector<Recordatorio> rec_a = a.recordatorios_de_hoy();
    os << a.hoy() << endl;
    os << "=====" << endl;
    for(int i = 0; i < rec_a.size(); i++){
        os << rec_a[i] << endl;
    }
    return os;
}
