#ifndef ImageProducer_h
#define ImageProducer_h

#include "classes/DelphesModule.h"

#include <deque>

class TObjArray;
class DelphesFormula;

class ImageProducer: public DelphesModule
{
 public:

  ImageProducer();
  ~ImageProducer();

  void Init();
  void Process();
  void Finish();

 private:

  Int_t ievt;

  Int_t nBinsEta;
  Double_t etaMin;
  Double_t etaMax;

  Int_t nBinsPhi;
  Double_t phiMin;
  Double_t phiMax;

  TIterator *fItInputArray; //!
  const TObjArray *fInputArray; //!


  ClassDef(ImageProducer, 1)
    };

#endif
