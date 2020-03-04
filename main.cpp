#include <iostream>

using namespace std;

/** LISTE CIRCULARE **/

/************************************************************/
/** Declararea clasei nod **/

 class nod
{
    /** date membru **/
    int data;

    nod* urm;

public:
    /** clasa Lista_circulara trebuie sa aiba acces
    la datele clasei nod **/

    friend class Lista_circulara;

    nod();

    nod(int valoare,nod *next);

    int getdata();

    void setdata(int data);

    nod* geturm();

    void seturm(nod* urm);
};

nod::nod()
   :data(0),urm(NULL)
{}

 nod::nod(int valoare,nod *next)
{
    data=valoare;
    urm=next;
}

int nod::getdata()
{
    return data;
}

void nod::setdata(int data)
{
    this->data=data;
}

nod* nod::geturm()
{
    return urm;
}

void nod::seturm(nod* urm)
{
    this->urm=urm;
}

/***********************************************************************/

/** Declararea clasei lista **/

class Lista_circulara
{
    nod *prim;

public:

    Lista_circulara();

    ~Lista_circulara();

    Lista_circulara(const Lista_circulara& c);

    Lista_circulara& operator= (const Lista_circulara& c);

    friend istream & operator >> (istream &in, Lista_circulara &ob);

    friend ostream & operator << (ostream &out,const Lista_circulara&  ob);

    void Golire_lista();

    void Adaugare_nod_final(int valoare);

    void Adaugare_nod_inceput(int valoare);

    void Adaugare_nod(int poz, int valoare);

    void stergere_nod_final();

    void stergere_nod_inceput();

    void stergere_nod(int poz);

    void sterge_k(int k);

    void inversare_legaturi();

    friend Lista_circulara operator + (Lista_circulara c1, Lista_circulara c2);
};

Lista_circulara::Lista_circulara()
{
    prim=NULL;
}

Lista_circulara::~Lista_circulara()
{
    nod *p,*q;
    p=prim;
    while(p->geturm()!=prim)
    {
      q=p->geturm();
      delete p;
      p=q;
    }
    delete p;
    prim=NULL;
}

Lista_circulara::Lista_circulara(const Lista_circulara& c)
{
      nod *x;
      prim=NULL;

      x=c.prim;
      if(c.prim==NULL)
       return;
      while(x->geturm()!=c.prim)
      {
          Adaugare_nod_final(x->getdata());
          x=x->geturm();

      }
       Adaugare_nod_final(x->getdata());
}

Lista_circulara Lista_circulara::operator= (const Lista_circulara& c)
{
      if(&c==this)
        return *this;
      Golire_lista();
      nod *x;
      x=c.prim;

      while(x->geturm()!=c.prim)
      {
          Adaugare_nod_final(x->getdata());
          x=x->geturm();
      }
      Adaugare_nod_final(x->getdata());

    return (*this);
}

istream & operator >> ( istream &in, Lista_circulara & ob)
{
    int n,x,i;
    in>>n;

    for(i=0;i<n;i++)
    {
     in>>x;
     ob.Adaugare_nod_final(x);
    }

    return in;
}

ostream & operator << ( ostream &out,const Lista_circulara& ob)
{
    nod *p;

    p=ob.prim;
    if(ob.prim==NULL)
        out<<"Lista circulara nu contine niciun element.\n";
    else
    {

    while(p->geturm()!=ob.prim)
    {
        out<<p->getdata()<<" ";
        p=p->geturm();
    }
    out<<p->getdata()<<" \n";
    }

    return out;
}

void Lista_circulara::Golire_lista()
{
    while(prim!=NULL)
    stergere_nod_inceput();
}

void Lista_circulara::Adaugare_nod_final(int valoare)
{
    nod *s,*t;

    s=new nod;
    s->data=valoare;
    t=prim;

    if(prim!=NULL)
    {
        while(t->urm!=prim)
            t=t->urm;

        t->urm=s;
        s->urm=prim;
    }
    else
        {s->urm=s;
         prim=s;
        }
}

void Lista_circulara::Adaugare_nod_inceput(int valoare)
{
    nod *s, *t;
    s=new nod;
    s->data=valoare;

    s->urm=prim;
    t=prim;

    if(prim==NULL)
    s->urm=s;

    else
    {
        while(t->urm!=prim)
            t=t->urm;
        t->urm=s;
    }
    prim=s;
}

void Lista_circulara::Adaugare_nod(int poz, int valoare)
{
    nod *p;
    int n=1;
    p=prim;
    while(p->urm!=prim)
     {
         n++;
         p=p->geturm();
     }
    if(poz>n+1)
    {
        cout<<"Pozitia data nu este valida";
        return;
    }
    //inserarea pe prima pozitie
    if(poz==1)
        Adaugare_nod_inceput(valoare);
    else

        if(poz==(n+1))
        Adaugare_nod_final(valoare);
        //inserarea in interiorul listei
        else
        {
            nod *s,*t;
            p=this->prim;

            while(poz>1)
            {s=p;
            p=p->geturm();
            poz--;
            }
            //valoarea va fi inserata intre p si s
            t= new nod;
            t->data=valoare;
            t->urm=p;
            s->urm=t;


        }
}

void Lista_circulara::stergere_nod_inceput()
{
    if(prim==NULL)
    {
     cout<<"Lista este deja vida.\n";
     return;
    }
    if(prim->urm==prim)
    {

     nod *p;
     p=prim;
     delete p;
     prim=NULL;
     return;
    }

    nod *t,*s;

    s=prim;
    t=prim->urm;

    while(s->urm!=prim)
        s=s->urm;

    s->urm=t;
    s=prim;

    delete s;
    prim=t;
}

void Lista_circulara::stergere_nod_final()
{
    if(prim==NULL)
    {
        cout<<"Lista este deja vida.\n";
        return;

    }
    if(prim->urm==prim)
    {
     delete prim;
     prim=NULL;
     return;
    }

    nod *t,*s;

    t=prim;
    while(t->urm->urm!=prim)
        t=t->urm;

    s=t->urm;
    t->urm=prim;

    delete s;
}

void Lista_circulara::stergere_nod(int poz)
{
    nod *p;
    int n=1;
    p=prim;
    while(p->urm!=prim)
     {
         n++;
         p=p->geturm();
     }
    if(poz>n)
    {
        cout<<"Pozitia data nu este valida";
        return;
    }

    if(poz==1)
        stergere_nod_inceput();
    else

        if(poz==n)
        stergere_nod_final();

        else
            //stergerea nodului din interior
        {
            nod *p,*s;
            p=prim;
            while(poz>1)
            {
                s=p;
                p=p->geturm();
                poz--;
            }
            s->urm=p->urm;
            delete p;

        }
}
void Lista_circulara::inversare_legaturi()
{
    nod *prev,*curent,*next,*t;

    t=prim;

    while(t->urm!=prim)
        t=t->urm;

    prev=t;
    curent=prev->urm;
    next=curent->urm;

    while(next!=prim)
    {
        curent->urm=prev;
        prev=curent;
        curent=next;
        next=next->urm;
    }
    curent->urm=prev;
    prim=t;
}

void Lista_circulara::sterge_k(int k)
{
    int nr,poz;

    nr=1;
    poz=1;
    nod *curent,*prev,*p;

    curent=prim;
    p=prim;

    while(p->urm!=prim)
    {
        nr++;
        p=p->urm;
    }

    prev=p;//ultimul element din lista


    if(k>nr)
        {cout<<"Imposibil de sters al k-ulea element.";
        return;
        }


      while(nr>1&&nr>=k)
      {
           int ok=0;
          if(poz%k==0)
          {
              cout<<curent->data<<" ";

              nod *s;

              prev->urm=curent->urm;
              s=curent;
              curent=prev->urm;
              delete s;

              nr--;
              ok=1;

          }
          if(ok==0)
          {
          prev=curent;
          curent=curent->urm;
          }
          poz++;

      }
      prim=prev;
}

 Lista_circulara operator+(Lista_circulara c1, Lista_circulara c2)
{
    Lista_circulara rez;
    nod *p;
    p=c1.prim;

    if(c1.prim==NULL)
        return c2;
    if(c2.prim==NULL)
        return c1;

    while(p->geturm()!=c1.prim)
    {
        rez.Adaugare_nod_final(p->getdata());
        p=p->geturm();
    }
    rez.Adaugare_nod_final(p->getdata());

    p=c2.prim;
    while(p->geturm()!=c2.prim)
    {
        rez.Adaugare_nod_final(p->getdata());
        p=p->geturm();
    }
    rez.Adaugare_nod_final(p->getdata());

    return rez;
}

int main()

{
   Lista_circulara a,b,rez,c;
   int x, poz,k;

   cout<<"Dati dimensiunea listei si elementele ce vor aparea in lista: \n";
   cin>>a;
   cout<<"Elementele listei sunt: \n";
   cout<<a;

   //test pentru inserare
   cout<<"\nTeste pentru inserare.\n";
   cout<<"\nDati o valoare ce va fi inserata in lista: \n";
   cin>>x;
   cout<<"\nDati o valoarea ce va reprezenta pozitia unde va fi inserata: \n";
   cin>>poz;
   a.Adaugare_nod(poz,x);
   cout<<a;

   //test pentru inserare
   cout<<"\nDati o valoare ce va fi inserata in lista: \n";
   cin>>x;
   cout<<"\nDati o valoarea ce va reprezenta pozitia unde va fi inserata: \n";
   cin>>poz;
   a.Adaugare_nod(poz,x);
   cout<<a;

   //test pentru inserare
   cout<<"Dati o valoare ce va fi inserata in lista: \n";
   cin>>x;
   cout<<"\nDati o valoarea ce va reprezenta pozitia unde va fi inserata: \n";
   cin>>poz;
   a.Adaugare_nod(poz,x);
   cout<<a;

   //test pentru stergerea unui element
   cout<<"\nTeste pentru stergere.\n";
   cout<<"\nDati pozitia de unde vreti sa fie efectuata stergerea: \n";
   cin>>poz;
   a.stergere_nod(poz);
   cout<<a;

   //test pentru stergerea unui element
   cout<<"\nDati pozitia de unde vreti sa fie efectuata stergerea: \n";
   cin>>poz;
   a.stergere_nod(poz);
   cout<<a;

   //test pentru stergerea unui element
   cout<<"\nDati pozitia de unde vreti sa fie efectuata stergerea: \n";
   cin>>poz;
   a.stergere_nod(poz);
   cout<<a;


   cout<<"\nDati dimensiunea listei si elementele ce vor aparea in lista: \n";
   cin>>b;
   cout<<"\nElementele listei sunt: \n";
   cout<<b;

   //test pentru inversarea legaturilor in lista
   cout<<"\nTest pentru inversarea legaturilor.\n";
   b.inversare_legaturi();
   cout<<"\nLista cu legaturile inversate este: \n";
   cout<<b;

   cout<<"\nDati dimensiunea listei si elementele ce vor aparea in lista: \n";
   cin>>c;
   cout<<"\nElementele listei sunt: \n";
   cout<<c;

   //test stergere din k in k pana va ramane un singur element in lista
   cout<<"\nStergerea elementelor din k in k:\n";
   cout<<"\nDati numarul k: \n";
   cin>>k;
   cout<<"\nElementele sunt sterse in urmatoarea oridne: \n";
   c.sterge_k(k);
   cout<<"\nLista dupa stergerea din "<<k<<" in "<<k<<" este:\n";
   cout<<c;

   //test pentru concatenarea listelor: a cu b
   cout<<"\nTest pentru concatenare (lista a cu lista b).\n";
   rez=a+b;
   cout<<"\nLista rez dupa concatenarea listei a cu lista b este: \n";
   cout<<rez;

  return 0;
}
