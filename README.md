use this to compile the .md file for pdf use:


pandoc "0 Full back up documentation .md" \
-o "0 Full back up documentation.pdf" \
--pdf-engine=xelatex \
--toc \
--number-sections
