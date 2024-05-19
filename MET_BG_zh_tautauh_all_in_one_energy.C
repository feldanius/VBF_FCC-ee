#include <iostream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

using namespace std;
int MET_BG_zh_tautauh_all_in_one_energy() {
    // Vector de archivos ROOT
    vector<string> filenames = {
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_015660911.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_058437289.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_094523955.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_160031364.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_175873169.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_192276123.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_043999218.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_090181769.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_116046380.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_162671919.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_tautauH_ecm365/events_186940475.root"

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
    TFile* outFile = new TFile("Missing_energy_BG_zh_tautauh_energy.root", "RECREATE");
    hist->Write();
    outFile->Close();

    // Limpieza
    delete hist;
    delete outFile;

    return 0;
}
