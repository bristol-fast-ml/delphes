#include "modules/ImageProducer.h"

#include "classes/DelphesClasses.h"
#include "classes/DelphesFactory.h"
#include "classes/DelphesFormula.h"

#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootFilter.h"
#include "ExRootAnalysis/ExRootClassifier.h"

#include "TMath.h"
#include "TString.h"
#include "TFormula.h"
#include "TRandom3.h"
#include "TObjArray.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"
#include "TH2D.h"
#include "TFile.h"

#include <algorithm> 
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

//------------------------------------------------------------------------------

ImageProducer::ImageProducer() :
  ievt(0), fItInputArray(0)
{

}

//------------------------------------------------------------------------------

ImageProducer::~ImageProducer()
{

}

//------------------------------------------------------------------------------

void ImageProducer::Init()
{
  TString filename = GetString("filename", "Images.root");

  nBinsEta = GetInt("nPixelEta", 20);
  etaMin   = GetDouble("etaMin", -5.);
  etaMax   = GetDouble("etaMax", -5.);

  nBinsPhi = GetInt("nPixelPhi", 12);
  
  // import input array(s)

  fInputArray = ImportArray(GetString("InputArray", ""));
  fItInputArray = fInputArray->MakeIterator();

  // create output directory
  file = new TFile(filename, "RECREATE");

}

//------------------------------------------------------------------------------

void ImageProducer::Finish()
{
  if(fItInputArray) delete fItInputArray;

  file->Close();
  if(file) delete file;

}

//------------------------------------------------------------------------------

void ImageProducer::Process()
{

  // create histogram
  Double_t phiMin   = -1*TMath::Pi();
  Double_t phiMax   = TMath::Pi();

  file->cd();
  const char* title = std::to_string(ievt).c_str();
  TH2D* h2 = new TH2D(title, "img", nBinsEta, etaMin, etaMax, nBinsPhi, phiMin, phiMax);

  Candidate *candidate;

  // loop over all input candidates
  fItInputArray->Reset();
  while((candidate = static_cast<Candidate*>(fItInputArray->Next())))
    {
      double eta = candidate->Position.Eta();
      double phi = candidate->Position.Phi();
      double p = candidate->Momentum.Pt();

      h2->Fill(eta, phi, p);
    }

  h2->Write();
  delete h2;

  ievt++;

}
