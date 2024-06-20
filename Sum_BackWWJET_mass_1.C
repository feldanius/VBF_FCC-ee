#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Sum_BackWWJET_mass_1() {
    const char* fileNames[] = {
    "BackWWJET_mass_events_000081890.root", "BackWWJET_mass_events_077177641.root", "BackWWJET_mass_events_124947653.root",
    "BackWWJET_mass_events_001084100.root", "BackWWJET_mass_events_077961119.root", "BackWWJET_mass_events_125410393.root",
    "BackWWJET_mass_events_001936135.root", "BackWWJET_mass_events_079581581.root", "BackWWJET_mass_events_125694683.root",
    "BackWWJET_mass_events_003311959.root", "BackWWJET_mass_events_079874852.root", "BackWWJET_mass_events_126621262.root",
    "BackWWJET_mass_events_008517319.root", "BackWWJET_mass_events_080551146.root", "BackWWJET_mass_events_126980955.root",
    "BackWWJET_mass_events_009112042.root", "BackWWJET_mass_events_081326715.root", "BackWWJET_mass_events_128303671.root",
    "BackWWJET_mass_events_009922998.root", "BackWWJET_mass_events_083171779.root", "BackWWJET_mass_events_131696833.root",
    "BackWWJET_mass_events_014470540.root", "BackWWJET_mass_events_083476787.root", "BackWWJET_mass_events_131936722.root",
    "BackWWJET_mass_events_021086660.root", "BackWWJET_mass_events_086285467.root", "BackWWJET_mass_events_132219478.root",
    "BackWWJET_mass_events_025952229.root", "BackWWJET_mass_events_086774567.root", "BackWWJET_mass_events_133605307.root",
    "BackWWJET_mass_events_026548305.root", "BackWWJET_mass_events_087040405.root", "BackWWJET_mass_events_137524898.root",
    "BackWWJET_mass_events_027513730.root", "BackWWJET_mass_events_087452123.root", "BackWWJET_mass_events_137590494.root",
    "BackWWJET_mass_events_028546045.root", "BackWWJET_mass_events_088117927.root", "BackWWJET_mass_events_142151386.root",
    "BackWWJET_mass_events_030420744.root", "BackWWJET_mass_events_089976236.root", "BackWWJET_mass_events_142326431.root",
    "BackWWJET_mass_events_031548033.root", "BackWWJET_mass_events_090775421.root", "BackWWJET_mass_events_143339192.root",
    "BackWWJET_mass_events_032448280.root", "BackWWJET_mass_events_091240706.root", "BackWWJET_mass_events_143879209.root",
    "BackWWJET_mass_events_036902764.root", "BackWWJET_mass_events_092739974.root", "BackWWJET_mass_events_144306993.root",
    "BackWWJET_mass_events_042360866.root", "BackWWJET_mass_events_093654693.root", "BackWWJET_mass_events_149880888.root",
    "BackWWJET_mass_events_043211856.root", "BackWWJET_mass_events_093871872.root", "BackWWJET_mass_events_150747171.root",
    "BackWWJET_mass_events_044550239.root", "BackWWJET_mass_events_094227409.root", "BackWWJET_mass_events_157525244.root",
    "BackWWJET_mass_events_045401282.root", "BackWWJET_mass_events_094831572.root", "BackWWJET_mass_events_164771774.root",
    "BackWWJET_mass_events_047601629.root", "BackWWJET_mass_events_096182593.root", "BackWWJET_mass_events_165573084.root",
    "BackWWJET_mass_events_048519618.root", "BackWWJET_mass_events_097812473.root", "BackWWJET_mass_events_166404736.root",
    "BackWWJET_mass_events_049205238.root", "BackWWJET_mass_events_098861309.root", "BackWWJET_mass_events_166556689.root",
    "BackWWJET_mass_events_050743883.root", "BackWWJET_mass_events_102710384.root", "BackWWJET_mass_events_169254437.root",
    "BackWWJET_mass_events_053823202.root", "BackWWJET_mass_events_105118674.root", "BackWWJET_mass_events_170034851.root",
    "BackWWJET_mass_events_057309409.root", "BackWWJET_mass_events_105861383.root", "BackWWJET_mass_events_170853329.root",
    "BackWWJET_mass_events_058259071.root", "BackWWJET_mass_events_106404137.root", "BackWWJET_mass_events_172262746.root",
    "BackWWJET_mass_events_058821537.root", "BackWWJET_mass_events_107743170.root", "BackWWJET_mass_events_172839947.root",
    "BackWWJET_mass_events_059805625.root", "BackWWJET_mass_events_109538064.root", "BackWWJET_mass_events_176643119.root",
    "BackWWJET_mass_events_060795865.root", "BackWWJET_mass_events_110263413.root", "BackWWJET_mass_events_184083150.root",
    "BackWWJET_mass_events_061978404.root", "BackWWJET_mass_events_111995477.root", "BackWWJET_mass_events_185820725.root",
    "BackWWJET_mass_events_063772509.root", "BackWWJET_mass_events_114994428.root", "BackWWJET_mass_events_186294283.root",
    "BackWWJET_mass_events_064075216.root", "BackWWJET_mass_events_116804196.root", "BackWWJET_mass_events_186696649.root",
    "BackWWJET_mass_events_067382959.root", "BackWWJET_mass_events_118835962.root", "BackWWJET_mass_events_188767652.root",
    "BackWWJET_mass_events_068617186.root", "BackWWJET_mass_events_121819232.root", "BackWWJET_mass_events_194083404.root",
    "BackWWJET_mass_events_069328331.root", "BackWWJET_mass_events_122228448.root", "BackWWJET_mass_events_196309639.root",
    "BackWWJET_mass_events_069637696.root", "BackWWJET_mass_events_123849603.root", "BackWWJET_mass_events_198386659.root",
    "BackWWJET_mass_events_071710976.root", "BackWWJET_mass_events_124008190.root"
};


    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 10.7165;  // en pb
    Double_t luminosity = 2.4e6;  // 2.4 ab^-1 expresado en pb^-1

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
        TH1F* hist = dynamic_cast<TH1F*>(file.Get("JET"));

        // Normaliza el histograma.
        if (hist) {
            hist->Scale(crossSection * luminosity);  // Normalización por sección transversal y luminosidad.

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
        const char* outputFileName = "BackWWJET_mass_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Sum_BackWWJET_mass_1();  // Llamada a la función principal.

    return 0;
}
