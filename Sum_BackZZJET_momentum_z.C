#include <iostream>
#include <TFile.h>
#include <TH1F.h>

int Sum_BackZZJET_momentum_z() {
    const char* fileNames[] = {
        "BackZZJET_momentum_z_events_001696302.root",
        "BackZZJET_momentum_z_events_003001058.root",
        "BackZZJET_momentum_z_events_004542872.root",
        "BackZZJET_momentum_z_events_008932909.root",
        "BackZZJET_momentum_z_events_014127399.root",
        "BackZZJET_momentum_z_events_014838097.root",
        "BackZZJET_momentum_z_events_019088425.root",
        "BackZZJET_momentum_z_events_020161630.root",
        "BackZZJET_momentum_z_events_024624496.root",
        "BackZZJET_momentum_z_events_024745237.root",
        "BackZZJET_momentum_z_events_027132528.root",
        "BackZZJET_momentum_z_events_029574438.root",
        "BackZZJET_momentum_z_events_030275741.root",
        "BackZZJET_momentum_z_events_030710516.root",
        "BackZZJET_momentum_z_events_031684841.root",
        "BackZZJET_momentum_z_events_032633846.root",
        "BackZZJET_momentum_z_events_033322185.root",
        "BackZZJET_momentum_z_events_034365885.root",
        "BackZZJET_momentum_z_events_034529401.root",
        "BackZZJET_momentum_z_events_036305182.root",
        "BackZZJET_momentum_z_events_040468238.root",
        "BackZZJET_momentum_z_events_041749934.root",
        "BackZZJET_momentum_z_events_046453381.root",
        "BackZZJET_momentum_z_events_047210663.root",
        "BackZZJET_momentum_z_events_051420387.root",
        "BackZZJET_momentum_z_events_052214341.root",
        "BackZZJET_momentum_z_events_052424361.root",
        "BackZZJET_momentum_z_events_052657692.root",
        "BackZZJET_momentum_z_events_053073147.root",
        "BackZZJET_momentum_z_events_053697318.root",
        "BackZZJET_momentum_z_events_053973825.root",
        "BackZZJET_momentum_z_events_056171721.root",
        "BackZZJET_momentum_z_events_056792216.root",
        "BackZZJET_momentum_z_events_060919902.root",
        "BackZZJET_momentum_z_events_062077114.root",
        "BackZZJET_momentum_z_events_062502766.root",
        "BackZZJET_momentum_z_events_062545514.root",
        "BackZZJET_momentum_z_events_067149354.root",
        "BackZZJET_momentum_z_events_067298136.root",
        "BackZZJET_momentum_z_events_068718613.root",
        "BackZZJET_momentum_z_events_071619177.root",
        "BackZZJET_momentum_z_events_077020967.root",
        "BackZZJET_momentum_z_events_078207694.root",
        "BackZZJET_momentum_z_events_083349007.root",
        "BackZZJET_momentum_z_events_084251123.root",
        "BackZZJET_momentum_z_events_087994603.root",
        "BackZZJET_momentum_z_events_090238630.root",
        "BackZZJET_momentum_z_events_092851225.root",
        "BackZZJET_momentum_z_events_093762749.root",
        "BackZZJET_momentum_z_events_098295024.root",
        "BackZZJET_momentum_z_events_098351043.root",
        "BackZZJET_momentum_z_events_101754828.root",
        "BackZZJET_momentum_z_events_102206217.root",
        "BackZZJET_momentum_z_events_103732607.root",
        "BackZZJET_momentum_z_events_105307492.root",
        "BackZZJET_momentum_z_events_107050183.root",
        "BackZZJET_momentum_z_events_109090276.root",
        "BackZZJET_momentum_z_events_113083371.root",
        "BackZZJET_momentum_z_events_113282591.root",
        "BackZZJET_momentum_z_events_113574790.root",
        "BackZZJET_momentum_z_events_115267766.root",
        "BackZZJET_momentum_z_events_115660713.root",
        "BackZZJET_momentum_z_events_116050595.root",
        "BackZZJET_momentum_z_events_121964585.root",
        "BackZZJET_momentum_z_events_125013562.root",
        "BackZZJET_momentum_z_events_125315792.root",
        "BackZZJET_momentum_z_events_126295024.root",
        "BackZZJET_momentum_z_events_129205309.root",
        "BackZZJET_momentum_z_events_130061441.root",
        "BackZZJET_momentum_z_events_133692815.root",
        "BackZZJET_momentum_z_events_135840565.root",
        "BackZZJET_momentum_z_events_137736367.root",
        "BackZZJET_momentum_z_events_138495552.root",
        "BackZZJET_momentum_z_events_140935835.root",
        "BackZZJET_momentum_z_events_140984869.root",
        "BackZZJET_momentum_z_events_144026616.root",
        "BackZZJET_momentum_z_events_144320233.root",
        "BackZZJET_momentum_z_events_145545538.root",
        "BackZZJET_momentum_z_events_145856382.root",
        "BackZZJET_momentum_z_events_146587224.root",
        "BackZZJET_momentum_z_events_147318350.root",
        "BackZZJET_momentum_z_events_148119516.root",
        "BackZZJET_momentum_z_events_148401866.root",
        "BackZZJET_momentum_z_events_150419675.root",
        "BackZZJET_momentum_z_events_152659631.root",
        "BackZZJET_momentum_z_events_155577588.root",
        "BackZZJET_momentum_z_events_155810265.root",
        "BackZZJET_momentum_z_events_158107052.root",
        "BackZZJET_momentum_z_events_158393095.root",
        "BackZZJET_momentum_z_events_158654042.root",
        "BackZZJET_momentum_z_events_158889908.root",
        "BackZZJET_momentum_z_events_159472455.root",
        "BackZZJET_momentum_z_events_159848992.root",
        "BackZZJET_momentum_z_events_160757782.root",
        "BackZZJET_momentum_z_events_162157559.root",
        "BackZZJET_momentum_z_events_162792908.root",
        "BackZZJET_momentum_z_events_163026739.root",
        "BackZZJET_momentum_z_events_164282910.root",
        "BackZZJET_momentum_z_events_166104738.root",
        "BackZZJET_momentum_z_events_167291958.root",
        "BackZZJET_momentum_z_events_168889214.root",
        "BackZZJET_momentum_z_events_169971509.root",
        "BackZZJET_momentum_z_events_170552925.root",
        "BackZZJET_momentum_z_events_172299325.root",
        "BackZZJET_momentum_z_events_175533196.root",
        "BackZZJET_momentum_z_events_175951222.root",
        "BackZZJET_momentum_z_events_176338267.root",
        "BackZZJET_momentum_z_events_180144303.root",
        "BackZZJET_momentum_z_events_182425053.root",
        "BackZZJET_momentum_z_events_185580770.root",
        "BackZZJET_momentum_z_events_187308074.root",
        "BackZZJET_momentum_z_events_188706220.root",
        "BackZZJET_momentum_z_events_192439824.root",
        "BackZZJET_momentum_z_events_193415571.root",
        "BackZZJET_momentum_z_events_194417088.root"
    };

    // Variables para almacenar las secciones transversales y las luminosidades.
    Double_t crossSection = 0.6428;  // en pb
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
        TH1F* hist = dynamic_cast<TH1F*>(file.Get("JET"));

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
        const char* outputFileName = "Sum_BackZZJET_momentum_z_histogram.root";
        TFile outputFileObj(outputFileName, "RECREATE");
        cumulativeHist->Write();
        outputFileObj.Close();

        std::cout << "Histograma normalizado guardado en " << outputFileName << std::endl;

        delete cumulativeHist;  // Libera la memoria del histograma acumulativo.
    }

    return 0;
}

int main() {
    Sum_BackZZJET_momentum_z();  // Llamada a la función principal.

    return 0;
}
