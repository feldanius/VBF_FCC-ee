#include <iostream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

using namespace std;
int MET_BG_zh_eeh_all_in_one_energy() {
    // Vector de archivos ROOT
    vector<string> filenames = {
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_018107429.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_104473316.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_117039771.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_130128294.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_173768499.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_047118042.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_107849662.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_118636096.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_153113508.root",
"/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_eeH_ecm365/events_182514790.root"

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
    TFile* outFile = new TFile("Missing_energy_BG_zh_eeh_energy.root", "RECREATE");
    hist->Write();
    outFile->Close();

    // Limpieza
    delete hist;
    delete outFile;

    return 0;
}
