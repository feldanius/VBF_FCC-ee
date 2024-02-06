#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Sum_BackWWMET_energy() {
    const char* fileNames[] = {
    "BackWWMET_energy_events_000081890.root", "BackWWMET_energy_events_077177641.root", "BackWWMET_energy_events_124947653.root",
    "BackWWMET_energy_events_001084100.root", "BackWWMET_energy_events_077961119.root", "BackWWMET_energy_events_125410393.root",
    "BackWWMET_energy_events_001936135.root", "BackWWMET_energy_events_079581581.root", "BackWWMET_energy_events_125694683.root",
    "BackWWMET_energy_events_003311959.root", "BackWWMET_energy_events_079874852.root", "BackWWMET_energy_events_126621262.root",
    "BackWWMET_energy_events_008517319.root", "BackWWMET_energy_events_080551146.root", "BackWWMET_energy_events_126980955.root",
    "BackWWMET_energy_events_009112042.root", "BackWWMET_energy_events_081326715.root", "BackWWMET_energy_events_128303671.root",
    "BackWWMET_energy_events_009922998.root", "BackWWMET_energy_events_083171779.root", "BackWWMET_energy_events_131696833.root",
    "BackWWMET_energy_events_014470540.root", "BackWWMET_energy_events_083476787.root", "BackWWMET_energy_events_131936722.root",
    "BackWWMET_energy_events_021086660.root", "BackWWMET_energy_events_086285467.root", "BackWWMET_energy_events_132219478.root",
    "BackWWMET_energy_events_025952229.root", "BackWWMET_energy_events_086774567.root", "BackWWMET_energy_events_133605307.root",
    "BackWWMET_energy_events_026548305.root", "BackWWMET_energy_events_087040405.root", "BackWWMET_energy_events_137524898.root",
    "BackWWMET_energy_events_027513730.root", "BackWWMET_energy_events_087452123.root", "BackWWMET_energy_events_137590494.root",
    "BackWWMET_energy_events_028546045.root", "BackWWMET_energy_events_088117927.root", "BackWWMET_energy_events_142151386.root",
    "BackWWMET_energy_events_030420744.root", "BackWWMET_energy_events_089976236.root", "BackWWMET_energy_events_142326431.root",
    "BackWWMET_energy_events_031548033.root", "BackWWMET_energy_events_090775421.root", "BackWWMET_energy_events_143339192.root",
    "BackWWMET_energy_events_032448280.root", "BackWWMET_energy_events_091240706.root", "BackWWMET_energy_events_143879209.root",
    "BackWWMET_energy_events_036902764.root", "BackWWMET_energy_events_092739974.root", "BackWWMET_energy_events_144306993.root",
    "BackWWMET_energy_events_042360866.root", "BackWWMET_energy_events_093654693.root", "BackWWMET_energy_events_149880888.root",
    "BackWWMET_energy_events_043211856.root", "BackWWMET_energy_events_093871872.root", "BackWWMET_energy_events_150747171.root",
    "BackWWMET_energy_events_044550239.root", "BackWWMET_energy_events_094227409.root", "BackWWMET_energy_events_157525244.root",
    "BackWWMET_energy_events_045401282.root", "BackWWMET_energy_events_094831572.root", "BackWWMET_energy_events_164771774.root",
    "BackWWMET_energy_events_047601629.root", "BackWWMET_energy_events_096182593.root", "BackWWMET_energy_events_165573084.root",
    "BackWWMET_energy_events_048519618.root", "BackWWMET_energy_events_097812473.root", "BackWWMET_energy_events_166404736.root",
    "BackWWMET_energy_events_049205238.root", "BackWWMET_energy_events_098861309.root", "BackWWMET_energy_events_166556689.root",
    "BackWWMET_energy_events_050743883.root", "BackWWMET_energy_events_102710384.root", "BackWWMET_energy_events_169254437.root",
    "BackWWMET_energy_events_053823202.root", "BackWWMET_energy_events_105118674.root", "BackWWMET_energy_events_170034851.root",
    "BackWWMET_energy_events_057309409.root", "BackWWMET_energy_events_105861383.root", "BackWWMET_energy_events_170853329.root",
    "BackWWMET_energy_events_058259071.root", "BackWWMET_energy_events_106404137.root", "BackWWMET_energy_events_172262746.root",
    "BackWWMET_energy_events_058821537.root", "BackWWMET_energy_events_107743170.root", "BackWWMET_energy_events_172839947.root",
    "BackWWMET_energy_events_059805625.root", "BackWWMET_energy_events_109538064.root", "BackWWMET_energy_events_176643119.root",
    "BackWWMET_energy_events_060795865.root", "BackWWMET_energy_events_110263413.root", "BackWWMET_energy_events_184083150.root",
    "BackWWMET_energy_events_061978404.root", "BackWWMET_energy_events_111995477.root", "BackWWMET_energy_events_185820725.root",
    "BackWWMET_energy_events_063772509.root", "BackWWMET_energy_events_114994428.root", "BackWWMET_energy_events_186294283.root",
    "BackWWMET_energy_events_064075216.root", "BackWWMET_energy_events_116804196.root", "BackWWMET_energy_events_186696649.root",
    "BackWWMET_energy_events_067382959.root", "BackWWMET_energy_events_118835962.root", "BackWWMET_energy_events_188767652.root",
    "BackWWMET_energy_events_068617186.root", "BackWWMET_energy_events_121819232.root", "BackWWMET_energy_events_194083404.root",
    "BackWWMET_energy_events_069328331.root", "BackWWMET_energy_events_122228448.root", "BackWWMET_energy_events_196309639.root",
    "BackWWMET_energy_events_069637696.root", "BackWWMET_energy_events_123849603.root", "BackWWMET_energy_events_198386659.root",
    "BackWWMET_energy_events_071710976.root", "BackWWMET_energy_events_124008190.root"
};


    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 10.7165;  // en pb
    Double_t luminosity = 1.5e-6;  // 1.5 ab^-1 expresado en pb^-1

    // Crea un histograma acumulativo para almacenar la suma de los histogramas normalizados.
    TH1F* cumulativeHist = nullptr;

    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); ++i) {
        // Abre el archivo ROOT.
        TFile file(fileNames[i]);

        // Comprueba si se abrió correctamente el archivo.
        if (file.IsZombie()) {
            std::cerr << "Error: No se pudo abrir el archivo " << fileNames[i] << std::endl;
            continue;
        }

        // Intenta obtener el histograma directamente del archivo.
        TH1F* hist = dynamic_cast<TH1F*>(file.Get("MET"));

        // Normaliza el histograma.
        if (hist) {
            hist->Scale(crossSection * luminosity / hist->GetEntries());  // Normalización por sección transversal y luminosidad.

            // Si es el primer archivo, crea el histograma acumulativo.
            if (!cumulativeHist) {
                cumulativeHist = new TH1F(*hist);
                cumulativeHist->SetDirectory(nullptr);  // Desvincula el histograma del archivo.
            } else {
                cumulativeHist->Add(hist);  // Agrega el histograma normalizado al histograma acumulativo.
            }
        } else {
            std::cerr << "Error: No se pudo obtener el histograma del archivo " << fileNames[i] << std::endl;
        }
    }

    if (cumulativeHist) {
        // Guarda el histograma acumulativo normalizado en un nuevo archivo.
        const char* outputFileName = "Sum_BackWWMET_energy_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Sum_BackWWMET_energy();  // Llamada a la función principal.

    return 0;
}
