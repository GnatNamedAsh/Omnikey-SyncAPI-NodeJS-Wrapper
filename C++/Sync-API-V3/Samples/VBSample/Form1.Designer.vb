<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class Form1
#Region "Windows Form Designer generated code "
	<System.Diagnostics.DebuggerNonUserCode()> Public Sub New()
		MyBase.New()
		'This call is required by the Windows Form Designer.
		InitializeComponent()
	End Sub
	'Form overrides dispose to clean up the component list.
	<System.Diagnostics.DebuggerNonUserCode()> Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
		If Disposing Then
			If Not components Is Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(Disposing)
	End Sub
	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Public ToolTip1 As System.Windows.Forms.ToolTip
	Public WithEvents CARDTYPE As System.Windows.Forms.ComboBox
	Public WithEvents READBUTTON As System.Windows.Forms.Button
	Public WithEvents WRITEBUTTON As System.Windows.Forms.Button
	Public WithEvents PRESENTPIN As System.Windows.Forms.Button
	Public WithEvents Frame4 As System.Windows.Forms.GroupBox
	Public WithEvents PIN As System.Windows.Forms.TextBox
	Public WithEvents Frame9 As System.Windows.Forms.GroupBox
	Public WithEvents Adress As System.Windows.Forms.TextBox
	Public WithEvents Frame11 As System.Windows.Forms.GroupBox
	Public WithEvents WRITEDATA As System.Windows.Forms.TextBox
	Public WithEvents Frame10 As System.Windows.Forms.GroupBox
	Public WithEvents BYTESTOREAD As System.Windows.Forms.TextBox
	Public WithEvents Frame8 As System.Windows.Forms.GroupBox
	Public WithEvents MESSAGETEXT As System.Windows.Forms.TextBox
	Public WithEvents Frame7 As System.Windows.Forms.GroupBox
	Public WithEvents I2CTYPE As System.Windows.Forms.ComboBox
	Public WithEvents INITI2CBUTTON As System.Windows.Forms.Button
	Public WithEvents Frame6 As System.Windows.Forms.GroupBox
	Public WithEvents ESTCONTEXTBUTTON As System.Windows.Forms.Button
	Public WithEvents RELCONTEXTBUTTON As System.Windows.Forms.Button
	Public WithEvents DISCONNECTBUTTON As System.Windows.Forms.Button
	Public WithEvents CONNECTBUTTON As System.Windows.Forms.Button
	Public WithEvents Frame3 As System.Windows.Forms.GroupBox
	Public WithEvents REPLYDATA As System.Windows.Forms.TextBox
	Public WithEvents Frame2 As System.Windows.Forms.GroupBox
	Public WithEvents ReaderList As System.Windows.Forms.ListBox
	Public WithEvents Frame1 As System.Windows.Forms.GroupBox
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.Frame4 = New System.Windows.Forms.GroupBox
        Me.CARDTYPE = New System.Windows.Forms.ComboBox
        Me.READBUTTON = New System.Windows.Forms.Button
        Me.WRITEBUTTON = New System.Windows.Forms.Button
        Me.PRESENTPIN = New System.Windows.Forms.Button
        Me.Frame10 = New System.Windows.Forms.GroupBox
        Me.Frame9 = New System.Windows.Forms.GroupBox
        Me.PIN = New System.Windows.Forms.TextBox
        Me.Frame11 = New System.Windows.Forms.GroupBox
        Me.Adress = New System.Windows.Forms.TextBox
        Me.WRITEDATA = New System.Windows.Forms.TextBox
        Me.Frame8 = New System.Windows.Forms.GroupBox
        Me.BYTESTOREAD = New System.Windows.Forms.TextBox
        Me.Frame7 = New System.Windows.Forms.GroupBox
        Me.MESSAGETEXT = New System.Windows.Forms.TextBox
        Me.Frame6 = New System.Windows.Forms.GroupBox
        Me.I2CTYPE = New System.Windows.Forms.ComboBox
        Me.INITI2CBUTTON = New System.Windows.Forms.Button
        Me.ESTCONTEXTBUTTON = New System.Windows.Forms.Button
        Me.RELCONTEXTBUTTON = New System.Windows.Forms.Button
        Me.Frame3 = New System.Windows.Forms.GroupBox
        Me.DISCONNECTBUTTON = New System.Windows.Forms.Button
        Me.CONNECTBUTTON = New System.Windows.Forms.Button
        Me.Frame2 = New System.Windows.Forms.GroupBox
        Me.REPLYDATA = New System.Windows.Forms.TextBox
        Me.Frame1 = New System.Windows.Forms.GroupBox
        Me.ReaderList = New System.Windows.Forms.ListBox
        Me.Frame4.SuspendLayout()
        Me.Frame10.SuspendLayout()
        Me.Frame9.SuspendLayout()
        Me.Frame11.SuspendLayout()
        Me.Frame8.SuspendLayout()
        Me.Frame7.SuspendLayout()
        Me.Frame6.SuspendLayout()
        Me.Frame3.SuspendLayout()
        Me.Frame2.SuspendLayout()
        Me.Frame1.SuspendLayout()
        Me.SuspendLayout()
        '
        'Frame4
        '
        Me.Frame4.BackColor = System.Drawing.SystemColors.Control
        Me.Frame4.Controls.Add(Me.CARDTYPE)
        Me.Frame4.Controls.Add(Me.READBUTTON)
        Me.Frame4.Controls.Add(Me.WRITEBUTTON)
        Me.Frame4.Controls.Add(Me.PRESENTPIN)
        Me.Frame4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame4.Location = New System.Drawing.Point(264, 168)
        Me.Frame4.Name = "Frame4"
        Me.Frame4.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame4.Size = New System.Drawing.Size(145, 161)
        Me.Frame4.TabIndex = 20
        Me.Frame4.TabStop = False
        Me.Frame4.Text = "Card Operations"
        '
        'CARDTYPE
        '
        Me.CARDTYPE.BackColor = System.Drawing.SystemColors.Window
        Me.CARDTYPE.Cursor = System.Windows.Forms.Cursors.Default
        Me.CARDTYPE.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.CARDTYPE.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CARDTYPE.ForeColor = System.Drawing.SystemColors.WindowText
        Me.CARDTYPE.Location = New System.Drawing.Point(8, 24)
        Me.CARDTYPE.Name = "CARDTYPE"
        Me.CARDTYPE.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.CARDTYPE.Size = New System.Drawing.Size(129, 22)
        Me.CARDTYPE.TabIndex = 24
        '
        'READBUTTON
        '
        Me.READBUTTON.BackColor = System.Drawing.SystemColors.Control
        Me.READBUTTON.Cursor = System.Windows.Forms.Cursors.Default
        Me.READBUTTON.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.READBUTTON.ForeColor = System.Drawing.SystemColors.ControlText
        Me.READBUTTON.Location = New System.Drawing.Point(8, 56)
        Me.READBUTTON.Name = "READBUTTON"
        Me.READBUTTON.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.READBUTTON.Size = New System.Drawing.Size(129, 25)
        Me.READBUTTON.TabIndex = 23
        Me.READBUTTON.Text = "Read Data"
        Me.READBUTTON.UseVisualStyleBackColor = False
        '
        'WRITEBUTTON
        '
        Me.WRITEBUTTON.BackColor = System.Drawing.SystemColors.Control
        Me.WRITEBUTTON.Cursor = System.Windows.Forms.Cursors.Default
        Me.WRITEBUTTON.Enabled = False
        Me.WRITEBUTTON.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.WRITEBUTTON.ForeColor = System.Drawing.SystemColors.ControlText
        Me.WRITEBUTTON.Location = New System.Drawing.Point(8, 120)
        Me.WRITEBUTTON.Name = "WRITEBUTTON"
        Me.WRITEBUTTON.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.WRITEBUTTON.Size = New System.Drawing.Size(129, 25)
        Me.WRITEBUTTON.TabIndex = 22
        Me.WRITEBUTTON.Text = "Write Data"
        Me.WRITEBUTTON.UseVisualStyleBackColor = False
        '
        'PRESENTPIN
        '
        Me.PRESENTPIN.BackColor = System.Drawing.SystemColors.Control
        Me.PRESENTPIN.Cursor = System.Windows.Forms.Cursors.Default
        Me.PRESENTPIN.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.PRESENTPIN.ForeColor = System.Drawing.SystemColors.ControlText
        Me.PRESENTPIN.Location = New System.Drawing.Point(8, 88)
        Me.PRESENTPIN.Name = "PRESENTPIN"
        Me.PRESENTPIN.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.PRESENTPIN.Size = New System.Drawing.Size(129, 25)
        Me.PRESENTPIN.TabIndex = 21
        Me.PRESENTPIN.Text = "Present Pin"
        Me.PRESENTPIN.UseVisualStyleBackColor = False
        '
        'Frame10
        '
        Me.Frame10.BackColor = System.Drawing.SystemColors.Control
        Me.Frame10.Controls.Add(Me.Frame9)
        Me.Frame10.Controls.Add(Me.Frame11)
        Me.Frame10.Controls.Add(Me.WRITEDATA)
        Me.Frame10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame10.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame10.Location = New System.Drawing.Point(8, 400)
        Me.Frame10.Name = "Frame10"
        Me.Frame10.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame10.Size = New System.Drawing.Size(249, 129)
        Me.Frame10.TabIndex = 16
        Me.Frame10.TabStop = False
        Me.Frame10.Text = "Write (Bytes)"
        '
        'Frame9
        '
        Me.Frame9.BackColor = System.Drawing.SystemColors.Control
        Me.Frame9.Controls.Add(Me.PIN)
        Me.Frame9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame9.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame9.Location = New System.Drawing.Point(160, 64)
        Me.Frame9.Name = "Frame9"
        Me.Frame9.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame9.Size = New System.Drawing.Size(65, 49)
        Me.Frame9.TabIndex = 25
        Me.Frame9.TabStop = False
        Me.Frame9.Text = "PIN"
        '
        'PIN
        '
        Me.PIN.AcceptsReturn = True
        Me.PIN.BackColor = System.Drawing.SystemColors.Window
        Me.PIN.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.PIN.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.PIN.ForeColor = System.Drawing.SystemColors.WindowText
        Me.PIN.Location = New System.Drawing.Point(8, 16)
        Me.PIN.MaxLength = 0
        Me.PIN.Name = "PIN"
        Me.PIN.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.PIN.Size = New System.Drawing.Size(49, 20)
        Me.PIN.TabIndex = 26
        '
        'Frame11
        '
        Me.Frame11.BackColor = System.Drawing.SystemColors.Control
        Me.Frame11.Controls.Add(Me.Adress)
        Me.Frame11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame11.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame11.Location = New System.Drawing.Point(160, 8)
        Me.Frame11.Name = "Frame11"
        Me.Frame11.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame11.Size = New System.Drawing.Size(81, 49)
        Me.Frame11.TabIndex = 18
        Me.Frame11.TabStop = False
        Me.Frame11.Text = "Adress (Hex)"
        '
        'Adress
        '
        Me.Adress.AcceptsReturn = True
        Me.Adress.BackColor = System.Drawing.SystemColors.Window
        Me.Adress.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.Adress.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Adress.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Adress.Location = New System.Drawing.Point(8, 16)
        Me.Adress.MaxLength = 0
        Me.Adress.Name = "Adress"
        Me.Adress.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Adress.Size = New System.Drawing.Size(65, 20)
        Me.Adress.TabIndex = 19
        Me.Adress.Text = "00"
        Me.Adress.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'WRITEDATA
        '
        Me.WRITEDATA.AcceptsReturn = True
        Me.WRITEDATA.BackColor = System.Drawing.SystemColors.Window
        Me.WRITEDATA.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.WRITEDATA.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.WRITEDATA.ForeColor = System.Drawing.SystemColors.WindowText
        Me.WRITEDATA.Location = New System.Drawing.Point(8, 16)
        Me.WRITEDATA.MaxLength = 0
        Me.WRITEDATA.Multiline = True
        Me.WRITEDATA.Name = "WRITEDATA"
        Me.WRITEDATA.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.WRITEDATA.Size = New System.Drawing.Size(145, 97)
        Me.WRITEDATA.TabIndex = 17
        '
        'Frame8
        '
        Me.Frame8.BackColor = System.Drawing.SystemColors.Control
        Me.Frame8.Controls.Add(Me.BYTESTOREAD)
        Me.Frame8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame8.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame8.Location = New System.Drawing.Point(264, 424)
        Me.Frame8.Name = "Frame8"
        Me.Frame8.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame8.Size = New System.Drawing.Size(145, 49)
        Me.Frame8.TabIndex = 14
        Me.Frame8.TabStop = False
        Me.Frame8.Text = "No. to Read (Hex)"
        '
        'BYTESTOREAD
        '
        Me.BYTESTOREAD.AcceptsReturn = True
        Me.BYTESTOREAD.BackColor = System.Drawing.SystemColors.Window
        Me.BYTESTOREAD.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.BYTESTOREAD.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.BYTESTOREAD.ForeColor = System.Drawing.SystemColors.WindowText
        Me.BYTESTOREAD.Location = New System.Drawing.Point(8, 16)
        Me.BYTESTOREAD.MaxLength = 0
        Me.BYTESTOREAD.Name = "BYTESTOREAD"
        Me.BYTESTOREAD.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.BYTESTOREAD.Size = New System.Drawing.Size(129, 20)
        Me.BYTESTOREAD.TabIndex = 15
        Me.BYTESTOREAD.Text = "100"
        Me.BYTESTOREAD.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'Frame7
        '
        Me.Frame7.BackColor = System.Drawing.SystemColors.Control
        Me.Frame7.Controls.Add(Me.MESSAGETEXT)
        Me.Frame7.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame7.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame7.Location = New System.Drawing.Point(8, 88)
        Me.Frame7.Name = "Frame7"
        Me.Frame7.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame7.Size = New System.Drawing.Size(249, 73)
        Me.Frame7.TabIndex = 10
        Me.Frame7.TabStop = False
        Me.Frame7.Text = "Message"
        '
        'MESSAGETEXT
        '
        Me.MESSAGETEXT.AcceptsReturn = True
        Me.MESSAGETEXT.BackColor = System.Drawing.SystemColors.Window
        Me.MESSAGETEXT.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.MESSAGETEXT.Enabled = False
        Me.MESSAGETEXT.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.MESSAGETEXT.ForeColor = System.Drawing.SystemColors.WindowText
        Me.MESSAGETEXT.Location = New System.Drawing.Point(8, 16)
        Me.MESSAGETEXT.MaxLength = 0
        Me.MESSAGETEXT.Multiline = True
        Me.MESSAGETEXT.Name = "MESSAGETEXT"
        Me.MESSAGETEXT.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.MESSAGETEXT.Size = New System.Drawing.Size(233, 49)
        Me.MESSAGETEXT.TabIndex = 11
        '
        'Frame6
        '
        Me.Frame6.BackColor = System.Drawing.SystemColors.Control
        Me.Frame6.Controls.Add(Me.I2CTYPE)
        Me.Frame6.Controls.Add(Me.INITI2CBUTTON)
        Me.Frame6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame6.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame6.Location = New System.Drawing.Point(264, 336)
        Me.Frame6.Name = "Frame6"
        Me.Frame6.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame6.Size = New System.Drawing.Size(145, 81)
        Me.Frame6.TabIndex = 7
        Me.Frame6.TabStop = False
        Me.Frame6.Text = "SCard2IC"
        '
        'I2CTYPE
        '
        Me.I2CTYPE.BackColor = System.Drawing.SystemColors.Window
        Me.I2CTYPE.Cursor = System.Windows.Forms.Cursors.Default
        Me.I2CTYPE.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.I2CTYPE.Enabled = False
        Me.I2CTYPE.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.I2CTYPE.ForeColor = System.Drawing.SystemColors.WindowText
        Me.I2CTYPE.Location = New System.Drawing.Point(8, 16)
        Me.I2CTYPE.Name = "I2CTYPE"
        Me.I2CTYPE.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.I2CTYPE.Size = New System.Drawing.Size(129, 22)
        Me.I2CTYPE.TabIndex = 13
        '
        'INITI2CBUTTON
        '
        Me.INITI2CBUTTON.BackColor = System.Drawing.SystemColors.Control
        Me.INITI2CBUTTON.Cursor = System.Windows.Forms.Cursors.Default
        Me.INITI2CBUTTON.Enabled = False
        Me.INITI2CBUTTON.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.INITI2CBUTTON.ForeColor = System.Drawing.SystemColors.ControlText
        Me.INITI2CBUTTON.Location = New System.Drawing.Point(8, 48)
        Me.INITI2CBUTTON.Name = "INITI2CBUTTON"
        Me.INITI2CBUTTON.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.INITI2CBUTTON.Size = New System.Drawing.Size(129, 25)
        Me.INITI2CBUTTON.TabIndex = 12
        Me.INITI2CBUTTON.Text = "Init"
        Me.INITI2CBUTTON.UseVisualStyleBackColor = False
        '
        'ESTCONTEXTBUTTON
        '
        Me.ESTCONTEXTBUTTON.BackColor = System.Drawing.SystemColors.Control
        Me.ESTCONTEXTBUTTON.Cursor = System.Windows.Forms.Cursors.Default
        Me.ESTCONTEXTBUTTON.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ESTCONTEXTBUTTON.ForeColor = System.Drawing.SystemColors.ControlText
        Me.ESTCONTEXTBUTTON.Location = New System.Drawing.Point(3, 25)
        Me.ESTCONTEXTBUTTON.Name = "ESTCONTEXTBUTTON"
        Me.ESTCONTEXTBUTTON.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ESTCONTEXTBUTTON.Size = New System.Drawing.Size(129, 25)
        Me.ESTCONTEXTBUTTON.TabIndex = 6
        Me.ESTCONTEXTBUTTON.Text = "Establish Context"
        Me.ESTCONTEXTBUTTON.UseVisualStyleBackColor = False
        '
        'RELCONTEXTBUTTON
        '
        Me.RELCONTEXTBUTTON.BackColor = System.Drawing.SystemColors.Control
        Me.RELCONTEXTBUTTON.Cursor = System.Windows.Forms.Cursors.Default
        Me.RELCONTEXTBUTTON.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.RELCONTEXTBUTTON.ForeColor = System.Drawing.SystemColors.ControlText
        Me.RELCONTEXTBUTTON.Location = New System.Drawing.Point(272, 128)
        Me.RELCONTEXTBUTTON.Name = "RELCONTEXTBUTTON"
        Me.RELCONTEXTBUTTON.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.RELCONTEXTBUTTON.Size = New System.Drawing.Size(129, 25)
        Me.RELCONTEXTBUTTON.TabIndex = 5
        Me.RELCONTEXTBUTTON.Text = "Release Context"
        Me.RELCONTEXTBUTTON.UseVisualStyleBackColor = False
        '
        'Frame3
        '
        Me.Frame3.BackColor = System.Drawing.SystemColors.Control
        Me.Frame3.Controls.Add(Me.DISCONNECTBUTTON)
        Me.Frame3.Controls.Add(Me.CONNECTBUTTON)
        Me.Frame3.Controls.Add(Me.ESTCONTEXTBUTTON)
        Me.Frame3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame3.Location = New System.Drawing.Point(264, 8)
        Me.Frame3.Name = "Frame3"
        Me.Frame3.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame3.Size = New System.Drawing.Size(145, 153)
        Me.Frame3.TabIndex = 4
        Me.Frame3.TabStop = False
        Me.Frame3.Text = "Common SCard Operations"
        '
        'DISCONNECTBUTTON
        '
        Me.DISCONNECTBUTTON.BackColor = System.Drawing.SystemColors.Control
        Me.DISCONNECTBUTTON.Cursor = System.Windows.Forms.Cursors.Default
        Me.DISCONNECTBUTTON.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.DISCONNECTBUTTON.ForeColor = System.Drawing.SystemColors.ControlText
        Me.DISCONNECTBUTTON.Location = New System.Drawing.Point(8, 88)
        Me.DISCONNECTBUTTON.Name = "DISCONNECTBUTTON"
        Me.DISCONNECTBUTTON.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.DISCONNECTBUTTON.Size = New System.Drawing.Size(129, 25)
        Me.DISCONNECTBUTTON.TabIndex = 9
        Me.DISCONNECTBUTTON.Text = "Disconnect"
        Me.DISCONNECTBUTTON.UseVisualStyleBackColor = False
        '
        'CONNECTBUTTON
        '
        Me.CONNECTBUTTON.BackColor = System.Drawing.SystemColors.Control
        Me.CONNECTBUTTON.Cursor = System.Windows.Forms.Cursors.Default
        Me.CONNECTBUTTON.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CONNECTBUTTON.ForeColor = System.Drawing.SystemColors.ControlText
        Me.CONNECTBUTTON.Location = New System.Drawing.Point(8, 56)
        Me.CONNECTBUTTON.Name = "CONNECTBUTTON"
        Me.CONNECTBUTTON.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.CONNECTBUTTON.Size = New System.Drawing.Size(129, 25)
        Me.CONNECTBUTTON.TabIndex = 8
        Me.CONNECTBUTTON.Text = "Connect"
        Me.CONNECTBUTTON.UseVisualStyleBackColor = False
        '
        'Frame2
        '
        Me.Frame2.BackColor = System.Drawing.SystemColors.Control
        Me.Frame2.Controls.Add(Me.REPLYDATA)
        Me.Frame2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame2.Location = New System.Drawing.Point(8, 168)
        Me.Frame2.Name = "Frame2"
        Me.Frame2.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame2.Size = New System.Drawing.Size(249, 225)
        Me.Frame2.TabIndex = 2
        Me.Frame2.TabStop = False
        Me.Frame2.Text = "Reply Data"
        '
        'REPLYDATA
        '
        Me.REPLYDATA.AcceptsReturn = True
        Me.REPLYDATA.BackColor = System.Drawing.SystemColors.Window
        Me.REPLYDATA.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.REPLYDATA.Font = New System.Drawing.Font("Courier New", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.REPLYDATA.ForeColor = System.Drawing.SystemColors.WindowText
        Me.REPLYDATA.Location = New System.Drawing.Point(8, 16)
        Me.REPLYDATA.MaxLength = 0
        Me.REPLYDATA.Multiline = True
        Me.REPLYDATA.Name = "REPLYDATA"
        Me.REPLYDATA.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.REPLYDATA.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.REPLYDATA.Size = New System.Drawing.Size(233, 201)
        Me.REPLYDATA.TabIndex = 3
        '
        'Frame1
        '
        Me.Frame1.BackColor = System.Drawing.SystemColors.Control
        Me.Frame1.Controls.Add(Me.ReaderList)
        Me.Frame1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame1.Location = New System.Drawing.Point(8, 8)
        Me.Frame1.Name = "Frame1"
        Me.Frame1.Padding = New System.Windows.Forms.Padding(0)
        Me.Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame1.Size = New System.Drawing.Size(249, 73)
        Me.Frame1.TabIndex = 0
        Me.Frame1.TabStop = False
        Me.Frame1.Text = "Readers"
        '
        'ReaderList
        '
        Me.ReaderList.BackColor = System.Drawing.SystemColors.Window
        Me.ReaderList.Cursor = System.Windows.Forms.Cursors.Default
        Me.ReaderList.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ReaderList.ForeColor = System.Drawing.SystemColors.WindowText
        Me.ReaderList.ItemHeight = 14
        Me.ReaderList.Location = New System.Drawing.Point(8, 16)
        Me.ReaderList.Name = "ReaderList"
        Me.ReaderList.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ReaderList.Size = New System.Drawing.Size(233, 46)
        Me.ReaderList.TabIndex = 1
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 14.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(417, 536)
        Me.Controls.Add(Me.Frame4)
        Me.Controls.Add(Me.Frame10)
        Me.Controls.Add(Me.Frame8)
        Me.Controls.Add(Me.Frame7)
        Me.Controls.Add(Me.Frame6)
        Me.Controls.Add(Me.RELCONTEXTBUTTON)
        Me.Controls.Add(Me.Frame3)
        Me.Controls.Add(Me.Frame2)
        Me.Controls.Add(Me.Frame1)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Location = New System.Drawing.Point(4, 23)
        Me.Name = "Form1"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Text = "Synchronous API VB Sample"
        Me.Frame4.ResumeLayout(False)
        Me.Frame10.ResumeLayout(False)
        Me.Frame10.PerformLayout()
        Me.Frame9.ResumeLayout(False)
        Me.Frame9.PerformLayout()
        Me.Frame11.ResumeLayout(False)
        Me.Frame11.PerformLayout()
        Me.Frame8.ResumeLayout(False)
        Me.Frame8.PerformLayout()
        Me.Frame7.ResumeLayout(False)
        Me.Frame7.PerformLayout()
        Me.Frame6.ResumeLayout(False)
        Me.Frame3.ResumeLayout(False)
        Me.Frame2.ResumeLayout(False)
        Me.Frame2.PerformLayout()
        Me.Frame1.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub
#End Region 
End Class