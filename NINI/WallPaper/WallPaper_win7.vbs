Set f =  CreateObject("Scripting.FileSystemObject").GetFile("f:\WallPapers\����\1352961531706.jpg")
Set vs = CreateObject("Shell.Application").NameSpace(f.ParentFolder.Path).ParseName(f.Name).Verbs
For Each v In vs
  If v.Name = "����Ϊ���汳��(&B)" Then v.DoIt
Next
WScript.Sleep 5000