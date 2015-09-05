import os.path

def prettify(fn):
  fn = ' '.join(x[0].upper() + x[1:] for x in fn.lower().split('-') if x != '')
  return fn 

if __name__ == '__main__':
  supported_src = {'.cpp': '\\includecpp', '.java': '\\includejava'};
 
  working_dir = os.path.normpath(os.getcwd())
  working_dir = os.path.join(working_dir, "src")
  
  for dn in os.listdir(working_dir):
    dirpath = os.path.join(working_dir, dn)
    if not os.path.isdir(dirpath):
      continue
    
    section = prettify(dn)
    print ("\\section{%s}" % (section))
    
    for fn in os.listdir(dirpath):
      filepath = os.path.join(dirpath, fn)
      _, file_ext = os.path.splitext(filepath)
      if not (os.path.isfile(filepath) and file_ext in supported_src.keys()):
        continue
      
      subsection = prettify(fn[:-len(file_ext)])
      file_relpath = os.path.join(".", os.path.relpath(filepath))
      file_relpath = file_relpath.replace('\\', '/')
      print ("%s{%s}{%s}" % (supported_src[file_ext], subsection, file_relpath))
