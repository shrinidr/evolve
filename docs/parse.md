Rules for parsing (the implications of having a package level segmentation)

1) A given rule's srcs can only contain files from its own package. 
Cross package usage must go through dep. 