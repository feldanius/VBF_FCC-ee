#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

using namespace std;

int jet_mass_histogram_bg_tt() {
    // Nombres de los archivos ROOT
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

    // Crear un histograma para la masa de los jets
    TH1F* hist_mass = new TH1F("hist_mass", "Masa de los jets", 100, 0, 400);

    // Iterar sobre los archivos
    for (const auto& filename : filenames) {
        // Abrir archivo ROOT
        TFile* file = TFile::Open(filename.c_str());
        if (!file) {
            cerr << "Error al abrir el archivo " << filename << endl;
            continue;
        }

        // Obtener el árbol de eventos
        TTree* tree = (TTree*)file->Get("events");
        if (!tree) {
            cerr << "No se pudo encontrar el árbol de eventos en " << filename << endl;
            file->Close();
            continue;
        }

        // Variables para almacenar la información de los jets
        float jet_mass;

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.mass", &jet_mass);

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Llenar el histograma con la masa del jet
            hist_mass->Fill(jet_mass);
        }

        // Cerrar el archivo ROOT
        file->Close();
    }

    // Guardar el histograma en un archivo ROOT
    TFile* output_file = TFile::Open("jet_mass_histogram_bg_tt.root", "RECREATE");
    if (output_file) {
        hist_mass->Write();
        output_file->Close();
    } else {
        cerr << "Error al abrir el archivo de salida" << endl;
    }

    // Limpiar la memoria
    delete hist_mass;

    return 0;
}
