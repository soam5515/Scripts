


TGraphErrors* TOF_walk(){


  Double_t startGamma=4.5;
  Double_t endGamma=5;


  if (gROOT->GetListOfSpecials()->IsEmpty()){
    cout<<"NO TCutG found \nMake a PulseShape cut first"<<endl;
    //    return;
  }


  Int_t channel=0;
  const Int_t numProjections=100;

  Double_t range=25000;
  Double_t startPoint=0;
  Double_t step =(range-startPoint)/numProjections;
  TH1D * projections[numProjections];

  TH2F * E_vs_TOF =new TH2F("E_vs_TOF","E_vs_TOF",1000,0,10,1000,startPoint,range);
  //TH2F * E_vs_TOF =new TH2F("E_vs_TOF","E_vs_TOF",1000,-20,20,1000,0,100);


  flt->Project("E_vs_TOF","energiesCor[2]:TOFW[2]",
         "channels[0]==2&&abs(TOF)<20&&abs(CorGOE)<0.5&&channels[2]==8");

  //flt->Project("E_vs_TOF","energies[1]:TOFW[1]");




  Double_t x[numProjections];
  Double_t y[numProjections];
  Double_t ex[numProjections];
  Double_t ey[numProjections];


  std::stringstream s;
  for (int i=0;i<numProjections;i++){
    Int_t bin1 = E_vs_TOF->GetYaxis()->FindBin(startPoint +i*step);
    Int_t bin2 = E_vs_TOF->GetYaxis()->FindBin(startPoint+ (i+1)*step);
    ///     Int_t bin2 = channel[j]->GetYaxis()->FindBin(600);
    x[i]=startPoint+i*step;
    ex[i]=0;
    
    s<<"chan"<<channel<<"_px"<<floor(startPoint+i*step)<<"_"<<floor(startPoint+(i+1)*step);
    
    projections[i]=E_vs_TOF->ProjectionX(s.str().c_str(),bin1,bin2);
    projections[i]->SetTitle("TOF");
    s.str("");
  }


  TF1 *f1 = new TF1("f1","gaus",startGamma,endGamma);
  

  TFitResultPtr result;
  for(int i=0;i<numProjections;i++){
    result = projections[i]->Fit("f1","QSNR");
    Int_t status=result;
    if (status==0){
      y[i]=result->Value(1);
      ey[i]=result->UpperError(1);
    } else {
      y[i]=0;
      ey[i]=0;

    }
    
    cout<<y[i]<<" "<<ey[i]<<endl;

  }

  TGraphErrors *gr =new TGraphErrors(numProjections,x,y,ex,ey);
  
  TCanvas *c = new TCanvas("c22");

  c->cd(1);
  gr->Draw("AL*");




  return gr;

}
