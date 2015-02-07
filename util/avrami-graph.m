#! /usr/bin/octave -qf

clear -all

function calculate_avrami(name, base_dir, output_dir, dimensions, min_x, max_x, type)

    csv_grow     = csvread(strcat(base_dir, "/", "grow_summary.csv"));
    csv_clusters = csvread(strcat(base_dir, "/", "clusters_details.csv"));

    data_a = [];
    data_b = [];


    for i = 1:size(csv_grow)(1)

        t    = csv_grow(i, 1);
        x    = csv_grow(i, 7);

        data_a = [data_a; t, x];

        if x >= min_x && x <= max_x
            data_b = [data_b; log(t) , log(-log(1-x))];
        end
    end
    
    for i = 1:size(csv_clusters)(1)
        radius    = csv_clusters(i, 3 + dimensions);
    end

    set (0, "defaultaxesfontname", "Helvetica")

    figure();
    plot(data_a(:,1), data_a(:,2), strcat(";", name, ";"));
    xlabel("t");
    ylabel("X");

    print(strcat(output_dir, "/", "graph-grow-linear.", type));

    figure();
    coeffs = polyfit(data_b(:,1), data_b(:,2), 1);
    fittedX = linspace(min(data_b(:,1)), max(data_b(:,1)), 200);
    fittedY = polyval(coeffs, fittedX);

    fit_params = sprintf("k = %f \n n = %f\n", exp(coeffs(2)), coeffs(1));

    plot(data_b(:,1), data_b(:,2), strcat(";", name, ";"), fittedX, fittedY, strcat(";", fit_params, ";"));
    xlabel("ln(t)");
    ylabel("ln(-ln(1-X))");

    print(strcat(output_dir, "/", "graph-grow-log.", type));
    
    
    for d = 1:dimensions
		figure();
		hist (csv_clusters(:, 1 + d), 30);
		xlabel(sprintf("position axis %d", d));
		ylabel("clusters");
		print(strcat(output_dir, "/", sprintf("hist-clusters-center-axis-%d.", d), type));
    end
   
    figure();
    hist (csv_clusters(:, 1 + dimensions + 1), 30);
    xlabel("creation time");
    ylabel("clusters");
    print(strcat(output_dir, "/", "hist-clusters-creation-time.", type));
    
    figure();
    hist (csv_clusters(:, 1 + dimensions + 2), 30);
    xlabel("radius");
    ylabel("clusters");
    print(strcat(output_dir, "/", "hist-clusters-radius.", type));
    
    figure();
    hist (csv_clusters(:, 1 + dimensions + 3), 30);
    xlabel("volume");
    ylabel("clusters");
    print(strcat(output_dir, "/", "hist-clusters-volume.", type));

end


#printf ("%s", program_name ());
arg_list = argv ();

if (size(arg_list) != 7)
    printf("Error running %s. Correct format is: %s <name> <csv_path> <output_dir> <dimensions> <min> <max> <type>\n");
    exit(-1);
end



#calculate_avrami("2d_constant", "example2d_constant/grow_summary.csv",     "/tmp/example2d_constant", 2,   0.10, 0.90, "pdf");


calculate_avrami(arg_list{1}, arg_list{2}, arg_list{3}, str2num(arg_list{4}), str2double(arg_list{5}),  str2double(arg_list{6}), arg_list{7});

