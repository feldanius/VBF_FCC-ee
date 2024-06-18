#include <iostream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

void create_jet_mass_histogram() {
    // Vector de nombres de archivos ROOT
    std::vector<std::string> filenames = {
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_008995949.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_034459462.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_067618566.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_088898158.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_107858353.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_158628525.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_177743949.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_192707663.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_019839222.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_061640142.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_071153275.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_090014287.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_129556080.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_174244458.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_178769856.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_027985022.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_065244791.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_075207014.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_090844778.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_138935081.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_176415634.root",
        "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/wzp6_ee_nunuH_ecm365/events_180776309.root"
    };

    // Crear un histograma para la masa de los jets
    TH1F* hist = new TH1F("hist_mass", "Masa de los jets", 100, 0, 400);

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

        // Variable para almacenar la masa del jet
        float jet_mass;

        // Configurar la dirección de la rama
        if (tree->SetBranchAddress("Jet.mass", &jet_mass) != 0) {
            std::cerr << "Error configurando la dirección de la hoja 'Jet.mass' en el archivo: " << filename << std::endl;
            file->Close();
            continue;
        }

        // Obtener el número de entradas en el árbol
        Long64_t nentries = tree->GetEntries();

        // Llenar el histograma con la masa de los jets
        for (Long64_t i = 0; i < nentries; i++) {
            tree->GetEntry(i);
            hist->Fill(jet_mass);
        }

        // Cerrar el archivo
        file->Close();
    }

    // Crear un archivo ROOT para guardar el histograma
    TFile* outFile = new TFile("jet_mass_histogram.root", "RECREATE");
    hist->Write();
    outFile->Close();

    // Liberar memoria
    delete hist;
    delete outFile;
}

int prueba() {
    create_jet_mass_histogram();
    return 0;
}
