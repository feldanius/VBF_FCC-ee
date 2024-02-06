void signalvsbackzzJET_nocut()
{
  //TFile *f4 = TFile::Open("Sum_BackZZJET_energy_histogram.root");
  //TFile *f4 = TFile::Open("Sum_BackZZJET_momentum_x_histogram.root");
  //TFile *f4 = TFile::Open("Sum_BackZZJET_momentum_y_histogram.root");
  //TFile *f4 = TFile::Open("Sum_BackZZJET_momentum_z_histogram.root");
  TFile *f4 = TFile::Open("Sum_BackZZJET_mass_histogram.root");
  TH1F *h4 = (TH1F*)f4->Get("JET"); // asi foton
  cout << h4 << endl;
  h4->SetFillColor(kBlue);
  
  //TFile *f2 = TFile::Open("Sum_BackWWJET_energy_histogram.root");
  //TFile *f2 = TFile::Open("Sum_BackWWJET_momentum_x_histogram.root");
  //TFile *f2 = TFile::Open("Sum_BackWWJET_momentum_y_histogram.root");
  //TFile *f2 = TFile::Open("Sum_BackWWJET_momentum_z_histogram.root");
  TFile *f2 = TFile::Open("Sum_BackWWJET_mass_histogram.root");
  TH1F *h2 = (TH1F*)f2->Get("JET"); // asi foton
  cout << h2 << endl;
  h4->SetFillColor(kRed);
  
  //TFile *f1 = TFile::Open("histosMETWrange.root");// con corte en 175 GeV y range
  //TH1F *h1 = (TH1F*)f1->Get("MET"); // asi foton
  //cout << h1 << endl;
  //h1->SetFillColor(kRed);
  

  //TFile *f3 = TFile::Open("Sum_SignalJET_energy_histogram.root");
  //TFile *f3 = TFile::Open("Sum_SignalJET_momentum_x_histogram.root");
  //TFile *f3 = TFile::Open("Sum_SignalJET_momentum_y_histogram.root");
  //TFile *f3 = TFile::Open("Sum_SignalJET_momentum_z_histogram.root");
  TFile *f3 = TFile::Open("Sum_SignalJET_mass_histogram.root");
  TH1F *h3 = (TH1F*)f3->Get("JET");
  cout << h3 << endl;
  h3->SetLineWidth(3);
  h3->SetLineStyle(9);
  h3->SetLineColor(6);
  h3->GetXaxis()->SetTitle(" [GeV]");
  h3->GetYaxis()->SetTitle("Eventos");
  h3->Draw("H");

  //THStack *hs = new THStack("hs","JET_energy [GeV] vs Events (1.4 ab-1)");
  //THStack *hs = new THStack("hs","JET_momentum_x [GeV] vs Events (1.4 ab-1)");
  //THStack *hs = new THStack("hs","JET_momentum_y [GeV] vs Events (1.4 ab-1)");
  //THStack *hs = new THStack("hs","JET_momentum_z [GeV] vs Events (1.4 ab-1)");
  THStack *hs = new THStack("hs","JET_mass [GeV] vs Events (1.4 ab-1)");
  
  //hs->Add(h1);
  hs->Add(h2);
  hs->Add(h4);
  hs->Draw("H");
  hs->GetXaxis()->SetTitle(" [GeV]");
  hs->GetYaxis()->SetTitle("Eventos");
  hs->Draw("H");
  h3->Draw("SAME");
  
  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
  legend->AddEntry(h3,"Signal","l");
  legend->AddEntry(h4,"BackZZ","f");
  legend->AddEntry(h2,"BackWW","f");
  legend->Draw("SAME");
  
}
