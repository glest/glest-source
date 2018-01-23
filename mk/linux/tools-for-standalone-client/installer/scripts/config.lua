local GAME_INSTALL_SIZE = 705000000;
local GAME_VERSION = "0.8.01";

local _ = MojoSetup.translate

Setup.Package
{
    vendor = "github.com/ZetaGlest",
    id = "zetaglest",
    description = _("ZetaGlest v" .. GAME_VERSION),
    version = GAME_VERSION,
    splash = "glestforumsheader.bmp",
    superuser = false,
    write_manifest = true,
    support_uninstall = true,
    recommended_destinations =
    {
        MojoSetup.info.homedir,
        "/opt/games",
        "/usr/local/games"
    },

    precheck = function(package)
	-- MojoSetup.msgbox('Test#1', MojoSetup.info.homedir .. '/zetaglest/uninstall-zetaglest.sh')

	local previousPath = ''
        if MojoSetup.platform.exists(MojoSetup.info.homedir .. '/zetaglest/uninstall-zetaglest.sh') then
		previousPath = MojoSetup.info.homedir .. '/zetaglest/'
	elseif MojoSetup.platform.exists('/opt/games/zetaglest/uninstall-zetaglest.sh') then
		previousPath = '/opt/games/zetaglest/'
	elseif MojoSetup.platform.exists('/usr/local/games/zegaglest/uninstall-zetaglest.sh') then
		previousPath = '/usr/local/games/zegaglest/'
	end

	if previousPath ~= '' then
		if MojoSetup.promptyn(_("ZetaGlest Uninstall Title"), _("ZetaGlest Uninstall Prompt") .. '\n\n[' .. previousPath .. ']') then
			os.execute(previousPath .. 'uninstall-zegaglest.sh')
		end

	end
    end,

    preinstall = function(package)
	local previousPath = ''
        if MojoSetup.platform.exists(MojoSetup.info.homedir .. '/zetaglest/mydata/') then
		previousPath = MojoSetup.info.homedir .. '/zetaglest/'
	elseif MojoSetup.platform.exists('/opt/games/zetaglest/mydata/') then
		previousPath = '/opt/games/zetaglest/'
	elseif MojoSetup.platform.exists('/usr/local/games/zetaglest/mydata/') then
		previousPath = '/usr/local/games/zetaglest/'
	end

	-- Move mod data folder to new location if we find it
	if previousPath ~= '' then
		local instPathData =  MojoSetup.info.homedir .. '/.zetaglest/'
		local instPath =  instPathData
		-- MojoSetup.msgbox('Moving mod folder','About to move mod folder from [' .. previousPath .. '] to [' .. instPath .. ']')

		os.execute('mkdir ' .. instPathData)
		os.execute('mv ' .. previousPath .. 'mydata/* ' .. instPath)
		os.execute('mv ' .. previousPath .. 'glestuser.ini ' .. instPath .. 'glestuser.ini')
	end
    end,

    postinstall = function(package)
	if MojoSetup.promptyn(_("ZetaGlest Visit Website Title"), _("ZetaGlest Visit Website Prompt")) then
        	MojoSetup.launchbrowser("http://zetaglest.org/get-started.html")
	end
    end,

    postuninstall = function(package)
	-- Cleanup additional files
	if MojoSetup.destination ~= '' then
		if MojoSetup.platform.exists(MojoSetup.destination .. '/lib/') then
			os.execute('rm -rf ' .. MojoSetup.destination .. '/lib/')
		end
		if MojoSetup.platform.exists(MojoSetup.destination .. '/.lib_bak/') then
			os.execute('rm -rf ' .. MojoSetup.destination .. '/.lib_bak/')
		end
		if MojoSetup.platform.exists(MojoSetup.destination) then
			os.execute('rm -rf ' .. MojoSetup.destination)
		end
	end
    end,

    Setup.Eula
    {
        description = _("ZetaGlest Game License"),
        source = _("docs/gnu_gpl_3.0.txt")
    },

    Setup.Eula
    {
        description = _("ZetaGlest Data License"),
        source = _("docs/cc-by-sa-3.0-unported.txt")
    },

    Setup.Readme
    {
        description = _("ZetaGlest README"),
        source = _("docs/README.txt")
    },

    Setup.Option
    {
        value = true,
        required = true,
        disabled = false,
        bytes = GAME_INSTALL_SIZE,
        description = _("ZetaGlest v" .. GAME_VERSION),

        Setup.File
        {
            -- Just install everything we see...
	    source = "base:///mgdata.tar.xz",
        },

        Setup.DesktopMenuItem
        {
            disabled = false,
            name = _("ZetaGlest v" .. GAME_VERSION),
            genericname = _("ZetaGlest"),
            tooltip = _("A real time strategy game."),
            builtin_icon = false,
            icon = "zetaglest.png",
            commandline = "%0/start_zetaglest",
            category = "Game;StrategyGame"
        },

        Setup.DesktopMenuItem
        {
            disabled = false,
            name = _("ZetaGlest Map Editor v" .. GAME_VERSION),
            genericname = _("ZetaGlest"),
            tooltip = _("A real time strategy game."),
            builtin_icon = false,
            icon = "zetaglest.png",
            commandline = "%0/start_zetaglest_mapeditor",
            category = "Game;StrategyGame",
            --mimetype = {"application/x-gbm", "application/mgm"}
        },

        Setup.DesktopMenuItem
        {
            disabled = false,
            name = _("ZetaGlest G3D Model Viewer v" .. GAME_VERSION),
            genericname = _("ZetaGlest"),
            tooltip = _("A real time strategy game."),
            builtin_icon = false,
            icon = "zetaglest.png",
            commandline = "%0/start_zetaglest_g3dviewer",
            category = "Game;StrategyGame",
            --mimetype = {"application/x-g3d"}
        },

        Setup.DesktopMenuItem
        {
            disabled = false,
            name = _("ZetaGlest Uninstall v" .. GAME_VERSION),
            genericname = _("ZetaGlest"),
            tooltip = _("A real time strategy game."),
            builtin_icon = false,
            icon = "zetaglest-uninstall.ico",
            commandline = "%0/uninstall-zetaglest.sh",
            category = "Game;StrategyGame"
        }

    }
}

-- end of config.lua ...

