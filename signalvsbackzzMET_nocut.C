void signalvsbackzzMET_nocut()
{
  //TFile *f4 = TFile::Open("Sum_BackZZMET_energy_histogram.root");
  //TFile *f4 = TFile::Open("Sum_BackZZMET_momentum_x_histogram.root");
  //TFile *f4 = TFile::Open("Sum_BackZZMET_momentum_y_histogram.root");
  //TFile *f4 = TFile::Open("Sum_BackZZMET_momentum_z_histogram.root");
  TFile *f4 = TFile::Open("Sum_BackZZMET_mass_histogram.root");
  TH1F *h4 = (TH1F*)f4->Get("MET"); // asi foton
  cout << h4 << endl;
  h4->SetFillColor(kBlue);
  

  
  //TFile *f1 = TFile::Open("histosMETWrange.root");// con corte en 175 GeV y range
  //TH1F *h1 = (TH1F*)f1->Get("MET"); // asi foton
  //cout << h1 << endl;
  //h1->SetFillColor(kRed);
  

  //TFile *f3 = TFile::Open("Sum_SignalMET_energy_histogram.root");
  //TFile *f3 = TFile::Open("Sum_SignalMET_momentum_x_histogram.root");
  //TFile *f3 = TFile::Open("Sum_SignalMET_momentum_y_histogram.root");
  //TFile *f3 = TFile::Open("Sum_SignalMET_momentum_z_histogram.root");
  TFile *f3 = TFile::Open("Sum_SignalMET_mass_histogram.root");
  TH1F *h3 = (TH1F*)f3->Get("MET");
  cout << h3 << endl;
  h3->SetLineWidth(3);
  h3->SetLineStyle(9);
  h3->SetLineColor(39);
  h3->GetXaxis()->SetTitle(" [GeV]");
  h3->GetYaxis()->SetTitle("Eventos");
  h3->Draw("H");

  //THStack *hs = new THStack("hs","MET_energy [GeV] vs Events (1.4 ab-1)");
  //THStack *hs = new THStack("hs","MET_momentum_x [GeV] vs Events (1.4 ab-1)");
  //THStack *hs = new THStack("hs","MET_momentum_y [GeV] vs Events (1.4 ab-1)");
  //THStack *hs = new THStack("hs","MET_momentum_z [GeV] vs Events (1.4 ab-1)");
  THStack *hs = new THStack("hs","MET_mass [GeV] vs Events (1.4 ab-1)");
  
  //hs->Add(h1);
  //hs->Add(h2);
  hs->Add(h4);
  hs->Draw("H");
  hs->GetXaxis()->SetTitle(" [GeV]");
  hs->GetYaxis()->SetTitle("Eventos");
  hs->Draw("H");
  h3->Draw("SAME");
  
}
