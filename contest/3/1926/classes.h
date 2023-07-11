#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *output;

template <typename T>
T *create ();

void _ac(const char *msg = "");
void _wa (const char *msg = "");

struct BaseObject {
  virtual ~BaseObject () {}
};

struct D : BaseObject {
  BaseObject *xiYgSY;

  D() : BaseObject() {
    printf("D()\n");
    xiYgSY = create<BaseObject>();
  }
  ~D () {}

  virtual void BoOuqp () {}
  virtual void SGEtsx () {}
};

struct G : BaseObject {
  D *jtliUM;
  BaseObject *xcFFyi;

  G() : BaseObject() {
    printf("G()\n");
    jtliUM = create<D>();
    xcFFyi = create<BaseObject>();
  }
  ~G () {}

  virtual void UNRWCB () {}
  virtual void zgWesH () {}
};

struct F : D {
  G *RpwEDv;
  BaseObject *jFNFBj;

  F () : D() {
    printf("F()\n");
    RpwEDv = create<G>();
    jFNFBj = create<BaseObject>();
  }
  ~F () {}

  virtual void ZwYexd () {}
};

struct E : BaseObject {
  F *jwzpbS;
  D *HzphKd;

  E() : BaseObject() {
    printf("E()\n");
    jwzpbS = create<F>();
    HzphKd = create<D>();
  }
  ~E () {}

  virtual void WNobSx () {}
};

struct J : G {
  BaseObject *drVYoE;

  J () : G() {
    printf("J()\n");
    drVYoE = create<BaseObject>();
  }
  ~J () {}

  void UNRWCB () override {
    if (jtliUM) jtliUM->SGEtsx();
  }
  virtual void ZhcDBt () {}
};

struct I : J {
  F *uQlRjt;

  I () : J() {
    printf("I()\n");
    uQlRjt = create<F>();
  }
  ~I () {}

  void ZhcDBt () override {}
};

struct C : D {
  E *vGYDBw;
  F *KtOmss;
  F *ldguno;

  C () : D() {
    printf("C()\n");
    vGYDBw = create<E>();
    KtOmss = create<F>();
    ldguno = create<F>();
  }
  ~C () {}

  virtual void nYrbFF () {}
  void SGEtsx () override {}
  void BoOuqp () override {}
  virtual void gPfxHw () {}
  virtual void ILrdEK () {
    _ac();
  }
};

struct H : C {
  BaseObject *rgrYhY;
  I *xaINAg;

  H () : C() {
    printf("H()\n");
    rgrYhY = create<BaseObject>();
    xaINAg = create<I>();
  }
  ~H () {}

  virtual void NcuKhz () {}
  virtual void dLWQXb () {}
  virtual void llYtjX () {}
};

struct K : G {
  BaseObject *RgXHMz;
  D *ZSwvyK;

  K () : G() {
    printf("K()\n");
    RgXHMz = create<BaseObject>();
    ZSwvyK = create<D>();
  }
  ~K () {}

  virtual void PeHNau () {
    if (jtliUM) jtliUM->BoOuqp();
    if (jtliUM) jtliUM->BoOuqp();
    if (jtliUM) jtliUM->SGEtsx();
  }
  virtual void POSzgU () {
    if (jtliUM) jtliUM->BoOuqp();
  }
  void zgWesH () override {
    if (jtliUM) jtliUM->BoOuqp();
  }
};

struct B : C {
  H *iczpxn;
  D *droWoh;
  J *QJInsm;

  B () : C() {
    printf("B()\n");
    iczpxn = create<H>();
    droWoh = create<D>();
    QJInsm = create<J>();
  }
  ~B () {}

  virtual void OOSoux () {}
  void gPfxHw () override {}
  void ILrdEK () override {}
  void SGEtsx () override {
    if (KtOmss) KtOmss->BoOuqp();
  }
};

struct A : B {
  E *ZQWYPf;
  K *uiWfjj;
  B *rkfigH;

  A () : B() {
    printf("A()\n");
    ZQWYPf = create<E>();
    uiWfjj = create<K>();
    rkfigH = create<B>();
  }
  ~A () {}

  void nYrbFF () override {
    if (iczpxn) iczpxn->ILrdEK();
    if (vGYDBw) vGYDBw->WNobSx();
    if (QJInsm) QJInsm->zgWesH();
    if (iczpxn) iczpxn->ILrdEK();
  }
  void OOSoux () override {
    if (iczpxn) iczpxn->ILrdEK();
    if (iczpxn) iczpxn->ILrdEK();
    if (iczpxn) iczpxn->ILrdEK();
    if (droWoh) droWoh->BoOuqp();
    if (vGYDBw) vGYDBw->WNobSx();
    if (droWoh) droWoh->BoOuqp();
  }
  virtual void xdAcVQ () {
    if (iczpxn) iczpxn->BoOuqp();
    if (iczpxn) iczpxn->ILrdEK();
    if (droWoh) droWoh->BoOuqp();
    if (iczpxn) iczpxn->ILrdEK();
    if (droWoh) droWoh->SGEtsx();
    if (iczpxn) iczpxn->ILrdEK();
  }
  virtual void YIaAzO () {
    if (iczpxn) iczpxn->ILrdEK();
    if (droWoh) droWoh->SGEtsx();
    if (iczpxn) iczpxn->ILrdEK();
    if (iczpxn) iczpxn->ILrdEK();
    if (ldguno) ldguno->ZwYexd();
    if (iczpxn) iczpxn->ILrdEK();
    if (QJInsm) QJInsm->UNRWCB();
  }
};

BaseObject *read () {
  char type[7];
  fscanf(output, "%6s", type);
  if (!strcmp(type, "null")) return nullptr;

  // 这里有上面声明的所有类的类名
  if (!strcmp(type, "D")) return new D;
  if (!strcmp(type, "G")) return new G;
  if (!strcmp(type, "F")) return new F;
  if (!strcmp(type, "E")) return new E;
  if (!strcmp(type, "J")) return new J;
  if (!strcmp(type, "I")) return new I;
  if (!strcmp(type, "C")) return new C;
  if (!strcmp(type, "H")) return new H;
  if (!strcmp(type, "K")) return new K;
  if (!strcmp(type, "B")) return new B;
  if (!strcmp(type, "A")) return new A;
  _wa("Unknown type.");
}

template <typename T>
T *create () {
  BaseObject *obj = read();
  if (obj == nullptr) return nullptr;
  T *ptr = dynamic_cast<T *>(obj);
  if (ptr != nullptr) return ptr;

  _wa("Unknown type.");
}
