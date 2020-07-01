Set f =  CreateObject("Scripting.FileSystemObject").GetFile("f:\WallPapers\其他\1r941b60-16.jpg")
Set vs = CreateObject("Shell.Application").NameSpace(f.ParentFolder.Path).ParseName(f.Name).Verbs
For Each v In vs
If v.Name = "设置为桌面背景(&B)" Then v.DoIt
Next
WScript.Sleep 500
