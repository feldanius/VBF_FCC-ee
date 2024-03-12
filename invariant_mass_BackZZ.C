#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"

using namespace std;

int invariant_mass_BackZZ() {
    // Directorio de entrada
    TString inputDirectory = "/eos/experiment/fcc/ee/generation/DelphesEvents/winter2023/IDEA/p8_ee_ZZ_ecm365/";

    // Nombres de los archivos ROOT
    vector<string> filenames = {
        "events_001696302.root", "events_032633846.root", "events_053973825.root", "events_087994603.root",
    "events_115267766.root", "events_144026616.root", "events_158889908.root", "events_175951222.root",
    "events_003001058.root", "events_033322185.root", "events_056171721.root", "events_090238630.root",
    "events_115660713.root", "events_144320233.root", "events_159472455.root", "events_176338267.root",
    "events_004542872.root", "events_034365885.root", "events_056792216.root", "events_092851225.root",
    "events_116050595.root", "events_145545538.root", "events_159848992.root", "events_180144303.root",
    "events_008932909.root", "events_034529401.root", "events_060919902.root", "events_093762749.root",
    "events_121964585.root", "events_145856382.root", "events_160757782.root", "events_182425053.root",
    "events_014127399.root", "events_036305182.root", "events_062077114.root", "events_098295024.root",
    "events_125013562.root", "events_146587224.root", "events_162157559.root", "events_185580770.root",
    "events_014838097.root", "events_040468238.root", "events_062502766.root", "events_098351043.root",
    "events_125315792.root", "events_147318350.root", "events_162792908.root", "events_187308074.root",
    "events_019088425.root", "events_041749934.root", "events_062545514.root", "events_101754828.root",
    "events_126295024.root", "events_148119516.root", "events_163026739.root", "events_188706220.root",
    "events_020161630.root", "events_046453381.root", "events_067149354.root", "events_102206217.root",
    "events_129205309.root", "events_148401866.root", "events_164282910.root", "events_192439824.root",
    "events_024624496.root", "events_047210663.root", "events_067298136.root", "events_103732607.root",
    "events_130061441.root", "events_150419675.root", "events_166104738.root", "events_193415571.root",
    "events_024745237.root", "events_051420387.root", "events_068718613.root", "events_105307492.root",
    "events_133692815.root", "events_152659631.root", "events_167291958.root", "events_194417088.root",
    "events_027132528.root", "events_052214341.root", "events_071619177.root", "events_107050183.root",
    "events_135840565.root", "events_155577588.root", "events_168889214.root",
    "events_029574438.root", "events_052424361.root", "events_077020967.root", "events_109090276.root",
    "events_137736367.root", "events_155810265.root", "events_169971509.root",
    "events_030275741.root", "events_052657692.root", "events_078207694.root", "events_113083371.root",
    "events_138495552.root", "events_158107052.root", "events_170552925.root",
    "events_030710516.root", "events_053073147.root", "events_083349007.root", "events_113282591.root",
    "events_140935835.root", "events_158393095.root", "events_172299325.root",
    "events_031684841.root", "events_053697318.root", "events_084251123.root", "events_113574790.root",
    "events_140984869.root", "events_158654042.root", "events_175533196.root"
    };

    // Crear un histograma para la masa invariante
    TH1F* hist_invariant_mass = new TH1F("hist_invariant_mass", "Masa invariante de los jets", 100, 0, 200);

    // Iterar sobre los archivos
    for (const auto& filename : filenames) {
        // Construir el nombre completo del archivo de entrada
        TString inputFilename = inputDirectory + filename;

        // Abrir archivo ROOT
        TFile* file = TFile::Open(inputFilename);
        if (!file) {
            cerr << "Error al abrir el archivo " << inputFilename << endl;
            continue;
        }

        // Obtener el árbol de eventos
        TTree* tree = (TTree*)file->Get("events");
        if (!tree) {
            cerr << "No se pudo encontrar el árbol de eventos en " << inputFilename << endl;
            file->Close();
            continue;
        }

        // Variables para almacenar la información de los jets
        vector<float> jet_energy(2);
        vector<float> jet_px(2);
        vector<float> jet_py(2);
        vector<float> jet_pz(2);

        // Conectar las variables del árbol con las variables locales
        tree->SetBranchAddress("Jet.energy", &jet_energy[0]);
        tree->SetBranchAddress("Jet.momentum.x", &jet_px[0]);
        tree->SetBranchAddress("Jet.momentum.y", &jet_py[0]);
        tree->SetBranchAddress("Jet.momentum.z", &jet_pz[0]);

        // Iterar sobre los eventos
        for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
            tree->GetEntry(i);

            // Crear los vectores Lorentz de los jets
            vector<TLorentzVector> jets;
            for (int j = 0; j < 2; ++j) {
                TLorentzVector jet;
                jet.SetPxPyPzE(jet_px[j], jet_py[j], jet_pz[j], jet_energy[j]);
                jets.push_back(jet);
            }

            // Calcular la masa invariante
            TLorentzVector dijet = jets[0] + jets[1];
            float invariant_mass = dijet.M();

            // Llenar el histograma con la masa invariante
            hist_invariant_mass->Fill(invariant_mass);
        }

        // Cerrar el archivo ROOT
        file->Close();
    }

    // Guardar el histograma en un archivo ROOT
    TFile* output_file = TFile::Open("invariant_mass_histogram_BackZZ.root", "RECREATE");
    if (output_file) {
        hist_invariant_mass->Write();
        output_file->Close();
    } else {
        cerr << "Error al abrir el archivo de salida" << endl;
    }

    // Limpiar la memoria
    delete hist_invariant_mass;

    return 0;
}
