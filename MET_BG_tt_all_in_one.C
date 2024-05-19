#include <iostream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

using namespace std;
int MET_BG_tt_all_in_one() {
    // Vector de archivos ROOT
    vector<string> filenames = {
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_002305720.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_040770007.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_061671341.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_109801805.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_147909069.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_176750629.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_186308065.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_030697089.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_041382953.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_069529080.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_112284451.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_160967503.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_179017298.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_188114698.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_034090110.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_041623160.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_082237208.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_132342737.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_174977492.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_179183191.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_197112999.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_036581856.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_057484114.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_095701099.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_144749341.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_175335143.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_tt_ecm365/events_183045919.root"
    };

    // Crear un histograma para la energía perdida
    TH1F* hist = new TH1F("missingET", "Missing Transverse Energy;E_{T}^{miss} (GeV);Events", 100, 0, 500);

    // Bucle sobre los archivos
    for (const auto& filename : filenames) {
        // Abre el archivo ROOT
        TFile* file = TFile::Open(filename.c_str());
        if (!file || file->IsZombie()) {
            std::cerr << "Error abriendo el archivo: " << filename << std::endl;
            continue;
        }

        // Obtener el árbol "events"
        TTree* tree = (TTree*)file->Get("events");
        if (!tree) {
            std::cerr << "Error obteniendo el árbol 'events' del archivo: " << filename << std::endl;
            file->Close();
            continue;
        }

        // Variable para almacenar la energía perdida
        float missingEnergy;

        // Configurar la dirección de la rama
        tree->SetBranchAddress("MissingET.energy", &missingEnergy);

        // Bucle sobre los eventos
        Long64_t nentries = tree->GetEntries();
        for (Long64_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            hist->Fill(missingEnergy);
        }

        // Cerrar el archivo
        file->Close();
    }

    // Crear un archivo ROOT para guardar el histograma
    TFile* outFile = new TFile("Missing_energy_BG_tt.root", "RECREATE");
    hist->Write();
    outFile->Close();

    // Limpieza
    delete hist;
    delete outFile;

    return 0;
}
