




void Thresh(){


  //This is the old data
  //  Double_t x[]={1083,3501,85.37,1527,53.73,151.29};

  //this is Jaspers runs
  //  Double_t x[]={1067.5,3442.5,78.39,1515,37.44,150.73};

  //from Jasper
  //  Double_t x[]={1071,3447,73,1510,38,154}; 
  //Done by sam using jaspers runs 368-370
  //  Double_t x[]={912.5,2907.5,68.76,1237.5,36.0929,117.459}; // chan 0
  Double_t x[]={1277.5,4112.5,101.123,1867.5,42.4504,182.592}; // chan 1




  Double_t xLiq[]={3346,10234,252.00,4593.00,65.44,494.28};
  Double_t exLiq[]={14,
		    14,
		    1.02,
		    3.00,
		    0.20,
		    0.95};

  Double_t per =0.05;

  Double_t ex[]={3,3,0.47,3,0.08,0.3};
  Double_t y[]={341,1062,33,478,26.3,59.5};

  for (int i=0;i<6;i++){
    
    ex[i]=sqrt(0*ex[i]*ex[i] + (per*x[i]*per*x[i]));
    exLiq[i]=sqrt(exLiq[i]*exLiq[i] + (per*xLiq[i]*per*xLiq[i]));
    
    
  }

  TGraphErrors * g= new TGraphErrors(6,x,y,ex,0);
  TGraphErrors * g1= new TGraphErrors(6,xLiq,y,exLiq,0);
  TCanvas * c = new TCanvas();
  //  c->Divide(2,1);
  c->cd(1);

  ///  gROOT->SetStyle("Pub");
  
  g->GetXaxis()->SetTitle("ADC Units");
  g->GetXaxis()->SetTitleSize(0.05);
  g->GetXaxis()->SetTitleOffset(1.4);

  g->GetYaxis()->SetTitle("Energy keV_{ee}");
  g->GetYaxis()->SetTitleSize(0.05);
  g->GetYaxis()->SetTitleOffset(1.4);

  g->SetMarkerSize(1.6);

  g->SetMarkerStyle(29);
  g->Draw("AP");
  g->SetTitle("Lenda Threshold");
  g->Fit("pol1");
  g->GetFunction("pol1")->SetLineColor(kBlack);
  g->GetFunction("pol1")->SetLineWidth(2);
  

  // c->cd(2);

  /*  
  g1->GetXaxis()->SetTitle("ADC Units");
 
  g1->GetYaxis()->SetTitle("Energy keV_{ee}");
  g1->GetXaxis()->SetTitleSize(0.04);
  g1->GetYaxis()->SetTitleSize(0.03);
  g1->GetYaxis()->SetTitleOffset(1.7);


  g1->SetMarkerStyle(2);
  g1->Draw("AP");
  g1->SetTitle("Trig Scint Threshold");
  g1->Fit("pol1");
  */

}
