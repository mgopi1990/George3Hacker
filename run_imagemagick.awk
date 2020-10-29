#!/usr/bin/awk -f 

## reads list of filenames.
## creates directory for names starting with ##
## generates files inside the created directory
## all these outputs are stored in output folder
## needs apt-get install imagemagick
## needs source file input/IMG.png
## needs fonts in /usr/share/fonts/

BEGIN {
	temp_file="output/temp.png"
}
{
	if (substr($0,1,2) == "##") {
		dirname = $0
		gsub(/^#+ */,"",dirname);
		gsub(/ *$/,"",dirname);
		gsub(/ +/,"_",dirname);
		system("mkdir output/" dirname);
		i = 1;
	} else if ($0 == "") {
		# do nothing 	
	} else {
	    fname = $0;
		gsub(/[()]*/,"",fname); gsub(/ +/,"_",fname); 
		fname = sprintf ("output/%s/%03d_%s.png", dirname, i, fname);

		printf (" processing %s for [%s]\r\n", fname, $0);
		system("convert -background none -font Carlito -pointsize 80 -stroke black -size 740x111 -gravity center -fill black caption:'" $0 "' -distort Arc 10 -fuzz 50% -transparent white output/temp.png");
		system("convert input/IMG.png output/temp.png -gravity northwest -geometry +324+1525 -composite -compose over " fname);

		i += 1;
	}
}
END {
	system("rm -f output/temp.png")
} 
