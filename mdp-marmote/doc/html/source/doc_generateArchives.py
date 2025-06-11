import os
import shutil
import zipfile
import sys
import re  # Pour les expressions régulières

import nbformat
from nbformat.v4 import new_code_cell, new_markdown_cell
# Reads and writes Jupyter notebook files.
# The nbformat library is a Python library used to work with Jupyter notebook files in various formats.
# It provides functions for reading, writing, and manipulating Jupyter notebooks.
from nbconvert import PythonExporter # Converts Jupyter notebooks to Python script files.

"""
@author = MB and PL and EH
@version = 1.0.2
@warning be executed in source directory  
@brief = Copying notebooks from the pytutos directory, rename them, adding cells 
         to manipulate marmote packages on Google Colab, create an archive. 
"""

# Configuration des images
IMAGE_MAPPINGS = {
    "Mitrani_chain.png": "https://marmote.gitlabpages.inria.fr/marmote/_images/Mitrani_chain.png", # pour AppLesson 1
    #"tandemQueue.png": "https://github.com/MoussaMS/_images/raw/main/tandemQueue.png", # pour AppLesonn 2
    #"geron.png": "https://github.com/MoussaMS/_images/raw/main/geron.png", # Pour MDPLesson 2 si le lien vers le site ne marche pas
    #"FourRooms.png": "https://github.com/MoussaMS/_images/raw/main/FourRooms.png" # Pour MDPLesson 4 

	"tandemQueue.png": "https://marmote.gitlabpages.inria.fr/marmote/_images/tandemQueue.png", # pour AppLesonn 2
    "geron.png": "https://marmote.gitlabpages.inria.fr/marmote/_images/geron.png", # pour MPDLesson 2
    "FourRooms.png": "https://marmote.gitlabpages.inria.fr/marmote/_images/FourRooms.png" # pour MDPLesson 4
}

def copy_rename_notebooks(source_directory,dest_directory):
	"""
	copy all the notebooks from source_directory in a directory dest_diretcoryand rename them for be transformed in colab notebooks
	
	:param source_directory directory in which norebooks are
	:param dest_directory destination directory
	"""
	#go to source_directory aka ../pytutos
	os.chdir(source_directory)
	#list and copy files
	for filename in os.listdir(os.getcwd()):
		if filename.endswith(".ipynb"):
			name=filename.rstrip(".ipynb")
			name=name+"_colab.ipynb"
			#print(name) 
			dest=os.path.join(dest_directory,name)
			shutil.copy(filename,dest)
	print("Notebooks copied and renamed in:",dest_directory)
					
def add_cells_condacolab_directory(directory):
	# Iterate through all files in the directory
	for filename in os.listdir(directory):
		if filename.endswith(".ipynb"):  # Check if the file is a notebook
			notebook_path = os.path.join(directory, filename)
			add_cells_condacolab(notebook_path)
	print("Notebooks modified for colab")

def add_cells_condacolab(notebook_path):
	"""
	Modifies notebooks for condacolab
	"""
	# Load the existing notebook
	with open(notebook_path, "r", encoding="utf-8") as f:
		notebook = nbformat.read(f, as_version=4)
	
	#read the title 
	cellule=notebook["cells"]
	cellule=cellule[0]
	#print("cellule",cellule,"type",type(cellule))
	titre=cellule['source']
	titre="# Colab worksheet for "+titre[2:]
	
	# Create the cells
	cell_text1 = new_markdown_cell(source=titre)
	cell_text2 = new_markdown_cell(source="## Install marmote on conda")
	cell_text3 = new_markdown_cell(source="To install `condacolab` ")
	cell_code4 = new_code_cell(source="!pip install -q condacolab\nimport condacolab\ncondacolab.install()\n!conda --version")
	cell_text5 = new_markdown_cell(source="To install `marmote`")
	cell_code6 = new_code_cell(source="!conda install -c marmote -c conda-forge marmote")
	cell_text7 = new_markdown_cell(source="You can now use marmote")
	
	# Insert the cells at the beginning of the notebook
	notebook["cells"] = [
		cell_text1,
		cell_text2,
		cell_text3,
		cell_code4,
		cell_text5,
		cell_code6,
		cell_text7,
	] + notebook["cells"]
	
	# Save the modified notebook
	with open(notebook_path, "w", encoding="utf-8") as f:
		nbformat.write(notebook, f)


def creating_colab_archive(archivename,directory):
	"""
	create the colab archive
	
	:param name of the archive
	:param directory where are the files to be archived
	"""
	#go into directory where are the files
	os.chdir(directory)
	archivename=archivename+'.zip'
	myZip = zipfile.ZipFile('./'+archivename, 'w', zipfile.ZIP_DEFLATED) # create archive (empty)
	#adding file
	for filename in os.listdir(os.getcwd()):
		if filename.endswith(".ipynb"):
			myZip.write('./'+filename)
	myZip.close()
	print("Archive", archivename ,"created from:",directory)	

	
def moving_cleaning_colab_archive(archivename,position,dest_directory):
	"""
	move the colab archive and delete old files
	
	:param name of the archive
	:param directory where are the files to be archived
	"""
	# go to the correct directory
	os.chdir(position)	
	#copy archive in the right place
	archivename=archivename+'.zip'
	dest=os.path.join(dest_directory,archivename)
	shutil.move(archivename,dest)
	print("Archive", archivename ,"moved in:",dest)
	for filename in os.listdir(os.getcwd()):
		if filename.endswith(".ipynb"):
			os.remove(filename)
			#print(filename+" removed")
	print("All colab.ipynb files removed")

def creating_cpp_archive(archivename,source,destination):
	"""
	Create cpp archive
	"""
	os.chdir(source)
	archivename=archivename+'.zip'
	myZip = zipfile.ZipFile(archivename, 'w', zipfile.ZIP_DEFLATED) # create archive (empty)
	#adding file
	for filename in os.listdir(os.getcwd()):
		if filename.endswith(".cpp"):
			myZip.write(filename)
		if filename.endswith(".mcl"):
			myZip.write(filename)
	myZip.close()
	print("Archive", archivename,"created from:", source)
	dest=os.path.join(destination,archivename)
	shutil.move(archivename,dest)
	print("Archive", archivename,"moved in:",dest)	


def creating_nb_archive(archivename,source,destination): 
	"""
	Create an archive of notebook files in source and put the archive in destination
	"""

	"""
	ASSOCIATED IMAGES IN SOURCE DIRECTORY AND PUT THE ARCHIVE IN DESTINATION
	"""
	os.chdir(source)
	# Find all notebook files AND IMAGES in the current directory
	files_to_archive = [] ## J'ai MODIFIE LE NOM POUR GENERALISER
	current_directory = os.getcwd()

	## SUPPORTED IMAGE EXTENSIONS
	image_extensions = ('.png', '.jpg', '.jpeg', '.gif', '.svg')
	########

	for f in os.listdir(current_directory):
		## I ADD FOR THE IMAGE TOO
		if f.endswith('.ipynb') or f.lower().endswith(image_extensions):
			files_to_archive.append(f)
	# Create a ZIP archive
	with zipfile.ZipFile(archivename, 'w', zipfile.ZIP_DEFLATED) as zipf:
		for file_to_archive in files_to_archive:
			## FOR RELATIVE PATH FILES
			zipf.write(file_to_archive)
		zipf.close()
	print("Archive", archivename, "created from:",source)
	# Move the ZIP archive to the destination directory
	shutil.move(archivename, os.path.join(destination_directory, archive))
	print("Archive", archivename,"moved in:",destination)

	
def copy_notebooks(source_directory,dest_directory):
	"""
	Copy notebooks from source to destination
	"""
	os.chdir(source_directory)
	#list and copy files
	for filename in os.listdir(os.getcwd()):
		if filename.endswith(".ipynb"): 
			dest=os.path.join(dest_directory,filename)
			shutil.copy(filename,dest)
	print("Notebooks copied from:",source_directory)
	print("Notebooks copied in:",dest_directory)


def creating_pythonFiles(source_directory,archive_name_py,destination_directory_pyex):
	"""
	Create python file from notebooks located in source directory and move them in destination
	"""
	os.chdir(source_directory)
	current_directory=os.getcwd()
	# Find all notebook files in the current directory
	notebook_files = []
	for f in os.listdir(current_directory):
		if f.endswith('.ipynb'):
			notebook_files.append(f)
	python_files = []
	# Convert the notebooks to Python files
	for notebook_file in notebook_files:
		notebook_path = os.path.join(current_directory, notebook_file)
		with open(notebook_path) as f:
			nb = nbformat.read(f, as_version=4)
			exporter = PythonExporter()
			script, _ = exporter.from_notebook_node(nb)
    
		python_file_name = notebook_file.replace('.ipynb', '.py')
		python_file_path = os.path.join(current_directory, python_file_name)
		with open(python_file_path, 'w') as f:
			f.write(script)
		python_files.append(python_file_path)
	print("Notebooks converted in python files")
	# Create a ZIP archive for the Python files
	with zipfile.ZipFile(archive_name_py, 'w',zipfile.ZIP_DEFLATED) as zipf:
		for python_file in python_files:
			zipf.write(python_file, os.path.basename(python_file))
		zipf.close()
	print("Archive",archive_name_py,"created from:",source_directory)
	# Move the ZIP archive to the destination directory
	shutil.move(archive_name_py, os.path.join(destination_directory_pyex, archive_name_py))
	print("Archive",archive_name_py,"moved in:",destination_directory_pyex)
	# Delete the Python files
	for python_file in python_files:
		os.remove(python_file)
	print("Python files deleted from: ",source_directory)	
	for nb_file in notebook_files:
		os.remove(nb_file)
	print("Notebooks files deleted from: ",source_directory)

## LA FONCTION POUR REMPLACER LE LIEN DES IMAGES EXISTANTES SUR LE SITE DE MARMOTE


def replace_images_for_colab(notebook_path, image_mappings):
    """
    Permet de Remplacer plusieurs images locales par leurs URLs distantes dans un notebook Colab.
    
    :param notebook_path: Chemin du notebook
    :param image_mappings: Dictionnaire {nom_fichier_local: url_distante}
    """
    if not notebook_path.endswith("_colab.ipynb"):
        return

    with open(notebook_path, "r", encoding="utf-8") as f:
        notebook = nbformat.read(f, as_version=4)

    replacements = {}
    for cell in notebook["cells"]:
        if cell["cell_type"] == "markdown" and "source" in cell:
            for local_img, remote_img in image_mappings.items():
                if f"<img src=\"./{local_img}\">" in cell["source"]:
                    cell["source"] = cell["source"].replace(
                        f"<img src=\"./{local_img}\">",
                        f"<img src=\"{remote_img}\">"
                    )
                    replacements[local_img] = True

    if replacements:
        with open(notebook_path, "w", encoding="utf-8") as f:
            nbformat.write(notebook, f)
        replaced = ", ".join(replacements.keys())
        print(f"Images remplacées dans {os.path.basename(notebook_path)}: {replaced}")
    else:
        print(f"Aucune image à remplacer dans {os.path.basename(notebook_path)}")
#################""

#main code
"""
We expect to run the script from ../script directory
in working directory ../doc/html/source/
If we are not in the direct directory
position="../doc/html/source/"        
os.chdir(position)
"""

#Test if we are in the correct directory
# get the absolute path
#root_dir = os.path.abspath(os.path.join(__file__, '..',".."))
#print(f"root {root_dir}")

# Get the current working directory path
current_directory=os.getcwd()
print(f"Working directory is : {current_directory}")
# Get the name
current_name=os.path.basename(current_directory)
if (current_name=="scripts"):
	position=os.path.join("..","doc","html","source")
	os.chdir(position)
	print("Change directory in : ",os.getcwd())
elif (current_name=="marmote"):
	position=os.path.join("doc","html","source")
	os.chdir(position)
	print("Change directory in : ",os.getcwd())
elif (current_name=="source"):
	print("No directory change",os.getcwd())
else:
	print("Wrong working directory. Program stops")
	sys.exit()
	
current_directory=os.getcwd()
print("Manage working directories and source directories")
#create and test the directory
source_d = os.path.join(current_directory,"pytutos")
notebooks_d = os.path.join(current_directory,"pytutos_colab")
# Get the directory where cpp are 
examples_directory = os.path.join(current_directory,'media')

if (not os.path.exists(source_d)):
	print("No source directory for Notebooks. Stop the programm")
	sys.exit()

if (not os.path.exists(examples_directory)):
	print("No source directory for cpp files. Stop the programm")
	sys.exit()

if (not os.path.exists(notebooks_d)):
	os.makedirs(notebooks_d, exist_ok=True)

print("1 - Generate Notebook for colab")
#copy and rename the file
copy_rename_notebooks(source_d,notebooks_d)
# go in directory source
os.chdir(current_directory)

# Call the function to add cells to all notebooks in the directory
add_cells_condacolab_directory(notebooks_d)

#  section pour le remplacement des images avec le mapping
print("\n1.2 - Mise à jour des liens d'images pour Colab")
for filename in os.listdir(notebooks_d):
    if filename.endswith(".ipynb"):
        notebook_path = os.path.join(notebooks_d, filename)
        replace_images_for_colab(notebook_path, IMAGE_MAPPINGS)
#################################################################

name="all_notebooks_colab"
creating_colab_archive(name,notebooks_d)

destination=os.path.join(current_directory,"instructions","all_nb_colab")
if (not os.path.exists(destination)):
	os.makedirs(destination, exist_ok=True)
	
moving_cleaning_colab_archive(name,notebooks_d,destination)


print("2 - Generate cpp archive")
# go in directory : "source"
os.chdir(current_directory)
# give the name of the archive
name="all_examples"
#manage destination directory
destination=os.path.join(current_directory,"instructions","all_ex")
# Ensure the destination directory exists
os.makedirs(destination, exist_ok=True)
creating_cpp_archive(name,examples_directory,destination)


print("3 - Generate nb archive")
# go in directory : "source"
os.chdir(current_directory)
#manage destination directory
destination_directory = os.path.join(current_directory,"instructions","all_nb")
# Name of the archive
archive = 'all_notebooks.zip'  
# Ensure the destination directory exists
os.makedirs(destination, exist_ok=True)
creating_nb_archive(archive,source_d,destination_directory)

print("4 - Generate python Files archive")
os.chdir(current_directory)
#copy notebooks
copy_notebooks(source_d,notebooks_d)
# Destination directory for Python files
destination_directory_pyex = os.path.join(current_directory,'instructions','all_pyex')  
# Ensure the destination directory exists
os.makedirs(destination_directory_pyex, exist_ok=True)
# Name of the archive for Python files
archive_name = 'all_pythons.zip'  
creating_pythonFiles(notebooks_d,archive_name,destination_directory_pyex)

#delete the temporary pytutos_colab
os.chdir(current_directory)
try: 
	os.rmdir(notebooks_d)
	print("Directory",notebooks_d,"deleted")
except OSError as e:
    # If it fails, inform the user.
    print("Error: %s - %s." % (e.filename, e.strerror))
	
