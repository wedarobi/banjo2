#ifndef __DLLS_H__
#define __DLLS_H__

#include "include/types.h"

#include "include/2.0L/ultra64.h"

#include "include/struct/object.h"
#include "include/struct/player.h"
#include "include/enum/map.h"

/**
 * This file is parsed by a script to automatically generate
 * the symbols the linker needs.
 * 
 * Functions MUST be named with the following prefix:
 * 
 *   DLL_{dllName}_
 * 
 *     where {dllName} is the name of the dll. e.g. "glzone"
 * 
 * It should be followed by {fnIdx}, but this is not strictly
 * enforced by the script.
 * 
 *   DLL_{dllName}_{fnIdx}_
 * 
 *     where {fnIdx} is the index of the public function
 *       (in decimal, NOT hex)
 * 
 *******************************************************************
 * Function declarations must be preceded with a magic comment that
 * hints to the script whether that function is exposed for that
 * respective build of the game. The magic comment does not have to
 * be on the same line as the declaration, but there should be
 * nothing else in-between them. If you want to comment the
 * declaration, put it before the magic comment.
 * 
 * Each character is used to encode whether the function is exposed
 * in that version. An "o" means it is exposed, a "-" means it is not.
 * With the four currently known versions:
 * 
 *                               @oooo
 *                          usa ──┘│││
 *                          jpn ───┘│|
 *                          eur ────┘|
 *                          aus ─────┘
 * 
 * Also, function declarations must appear in the same order that they
 * appear in the game.
 * 
 * Note: The "counting" system is inflexible and wouldn't work if
 * function order was shuffled between versions, but there is no
 * instance of this in any version of Tooie.
 * 
 * Do not modify the dll name comments (the "$ anseq" etc. ones).
 * 
 * IMPORTANT:
 * If you add a declaration for a function for a previously unused
 * DLL, you MUST allocate a line for EVERY SINGLE pub func for that
 * DLL, and you MUST fill in the magic comments appropriately for
 * each declaration. You do not need to make a declaration for each
 * though, just the magic comments.
 */

/* $ anseq */
/* $ baairbar */
/* $ baalarm */
/* $ baattach */
/* $ bababykaz */
/* $ babackpack */
/* $ babee */
/* $ baboost */
/* $ babounce */
/* $ babuzz */
/* $ bacough */
/* $ badata */
/* $ badeathmatch */
/* $ badialog */
/* $ badrone */
/* $ badronemem */
/*@oooo*/ void DLL_badronemem_00(PlayerObj *b, u32 size);
/*@oooo*/ void DLL_badronemem_01(PlayerObj *b);
/*@oooo*/ void DLL_badronemem_02(u32);
/*@oooo*/ void DLL_badronemem_03(PlayerObj *b);
/* $ baduo */
/* $ badust */
/* $ baeggaim */
/* $ baeggcursor */
/* $ baeggfire */
/* $ baeggsetup */
/* $ baflameline */
/* $ baflamethrower */
/* $ bafly */
/* $ bafpctrl */
/* $ bahitspline */
/* $ bahold */
/* $ bainvisible */
/* $ bakaztorpedo */
/* $ bamotor */
/* $ bamovegoto */
/* $ bamovehover */
/* $ bamoveledge */
/*@oooo*/ u32  DLL_bamoveledge_00(void);
/*@oooo*/ void DLL_bamoveledge_01(u32);
/*@oooo*/ void DLL_bamoveledge_02(u32);
/*@oooo*/ void DLL_bamoveledge_03(PlayerObj *b);
/* $ bamovespline */
/* $ bamovethrust */
/* $ bamum */
/* $ bapackctrl */
/* $ bapreload */
/* $ bapulse */
/* $ bareact */
/* $ basetup */
/* $ bashake */
/* $ bashoes */
/* $ bashoessuck */
/* $ basnowball */
/* $ baspin */
/* $ basquash */
/* $ bastatemem */
/*@oooo*/ void DLL_bastatemem_00(PlayerObj *b, u32 size);
/*@oooo*/ void DLL_bastatemem_01(PlayerObj *b);
/*@oooo*/ void DLL_bastatemem_02(u32);
/*@oooo*/ void DLL_bastatemem_03(PlayerObj *b);
/* $ basub */
/* $ basudie */
/* $ baswim */
/* $ batimer */
/* $ batranslate */
/* $ bavan */
/* $ bawandglow */
/* $ bawasher */
/* $ bawobble */
/* $ bsbabykaz */
/* $ bsbanbflip */
/* $ bsbanpackwhack */
/* $ bsbansack */
/* $ bsbanshack */
/* $ bsbansnooze */
/* $ bsbanswim */
/* $ bsbbarge */
/* $ bsbbilldrill */
/* $ bsbbuster */
/* $ bsbee */
/* $ bsbeefly */
/* $ bsbeemain */
/* $ bsbeggass */
/* $ bsbegghead */
/* $ bsbflap */
/* $ bsbflip */
/* $ bsbfly */
/* $ bsbkflamethrower */
/* $ bsblongleg */
/* $ bsbpeck */
/* $ bsbreegullbash */
/* $ bsbshock */
/* $ bsbswim */
/* $ bsbtrot */
/* $ bsbwhirl */
/* $ bscarry */
/* $ bschokedie */
/* $ bsclaw */
/* $ bsclimb */
/* $ bscrashout */
/* $ bscrouch */
/* $ bsdie */
/* $ bsdrone */
/* $ bsdronebitten */
/* $ bsdronebubbled */
/* $ bsdronefalldie */
/* $ bsdronefired */
/* $ bsdronegoto */
/* $ bsdronejump */
/* $ bsdronelook */
/* $ bsdroneslide */
/* $ bsdronesuckunder */
/* $ bsdronevanish */
/* $ bsdronewaitbabykaz */
/* $ bsdronexform */
/* $ bsfirstp */
/* $ bsjig */
/* $ bsjump */
/* $ bskaz */
/* $ bskazcrouch */
/* $ bskazdie */
/* $ bskazeggass */
/* $ bskazegghead */
/* $ bskazflamethrower */
/* $ bskazfly */
/* $ bskazglide */
/* $ bskazhatch */
/* $ bskazjump */
/* $ bskazmove */
/* $ bskazow */
/* $ bskazpaddle */
/* $ bskazshock */
/* $ bskazshoesspringjump */
/* $ bskazshoessuckspline */
/* $ bskazspring */
/* $ bskazstill */
/* $ bskazstilt */
/* $ bskaztorpedo */
/* $ bskazwingwhack */
/* $ bsledge */
/* $ bsmum */
/* $ bsmumattack */
/* $ bsmumcast */
/* $ bsmummove */
/* $ bsmumsplat */
/* $ bsmumstill */
/* $ bsmumswim */
/* $ bsow */
/* $ bsrebound */
/* $ bsrest */
/* $ bsride */
/* $ bssilowait */
/* $ bssnowball */
/* $ bssplat */
/* $ bssplitup */
/* $ bsstand */
/* $ bsstatue */
/* $ bsstonehead */
/* $ bssub */
/* $ bsswim */
/* $ bstalk */
/* $ bstaxi */
/* $ bsthrow */
/* $ bstimeout */
/* $ bstnt */
/* $ bstntswim */
/* $ bstrexlarge */
/* $ bstrexsmall */
/* $ bsturn */
/* $ bstwirl */
/* $ bsvan */
/* $ bsvanswim */
/* $ bswalk */
/* $ bswasher */
/* $ cadbfunc */
/* $ cadbio */
/* $ cadbmgrDll */
/* $ capod */
/* $ ch1pfreeze */
/* $ ch2dbaddy */
/* $ chLagoonInnBlockedWall */
/* $ chTalTorpWall */
/* $ chalienbeam */
/* $ chaliendad */
/* $ chalienkids */
/* $ chamazongoldhordeofficial */
/* $ chamazonstadiumguard */
/* $ chanemone */
/* $ changlerboss */
/* $ changlerbossbubble */
/* $ changlerbossdoor */
/* $ changlerbossflare */
/* $ chanim */
/* $ chappearfx */
/* $ charea51gate */
/* $ charmouredcaveman */
/* $ chattract */
/* $ chbabydino */
/* $ chbadbeehive */
/* $ chbaddieDll */
/* $ chbaddiesetup */
/* $ chbadjinjo */
/* $ chbadshad */
/* $ chballoonbomb */
/* $ chballoonburst */
/* $ chbanjoctrl */
/* $ chbanjocurrent */
/* $ chbeanstalkseed */
/* $ chbeehive */
/* $ chbigfoot */
/* $ chbiggafoot */
/* $ chbigterrysbits */
/* $ chbigtopticket */
/* $ chbilldrillboulder */
/* $ chbilldrillplate */
/* $ chbkcart */
/* $ chblackeye */
/* $ chblink */
/* $ chbobpanel */
/* $ chboggy */
/* $ chboggyboy */
/* $ chboggyfatboy */
/* $ chboggyfish */
/* $ chboggygirl */
/* $ chboggykids */
/* $ chboggykidshome */
/* $ chboilerboss */
/* $ chboilerbossdoor */
/* $ chboilerid */
/* $ chbonfirecavern */
/* $ chbosskogsdoor */
/* $ chbottlesdead */
/* $ chbottlesfamily */
/* $ chbottlesparty */
/* $ chbottlesplantgrill */
/* $ chbounce */
/* $ chbouncycastle */
/* $ chboxingglove */
/* $ chbubble */
/* $ chbubbleelevator */
/* $ chburgerstand */
/* $ chcablecar */
/* $ chcablespark */
/* $ chcactusofstrength */
/* $ chcamerawibble */
/* $ chcamwaypoint */
/* $ chcanarymarycage */
/* $ chcaptainblubber */
/* $ chcastleshockpadswitch */
/* $ chcauldronenergybars */
/* $ chcauldronentrydoor */
/* $ chcaveofhorrorsdoors */
/* $ chcheato */
/* $ chcheatomenu */
/* $ chcheatopage */
/* $ chchompaslunch */
/* $ chchuffy */
/* $ chchuffycont */
/* $ chchuffyglow */
/* $ chclimbbase */
/* $ chclinker */
/* $ chclockworkmouse */
/* $ chcoderoombits */
/* $ chcoderoomdoor */
/* $ chcollballcontrol */
/* $ chcolldoors */
/* $ chconga */
/* $ chcrackarchwall */
/* $ chcrashmat */
/* $ chcrate */
/* $ chcredits */
/* $ chcrusher */
/* $ chcrusherboulder */
/* $ chcrystalbaddie */
/* $ chdeflect */
/* $ chdiggerboss */
/* $ chdiggerbossbattery */
/* $ chdiggerbossdeflect */
/* $ chdiggerbossdoor */
/* $ chdiggerbossinterior */
/* $ chdiggerbossshell */
/* $ chdiggerfly */
/* $ chdiggerground */
/* $ chdiggergroundgen */
/* $ chdingpot */
/* $ chdinoboss */
/* $ chdinocoaster */
/* $ chdinofamilyfx */
/* $ chdinofamilymissing */
/* $ chdinofamilymother */
/* $ chdinofamilysick */
/* $ chdinofamilysmall */
/* $ chdinofoot */
/* $ chdinoroargrill */
/* $ chdinoswitches */
/* $ chdinotraindoor */
/* $ chdinotraindoorswitch */
/* $ chdippy */
/* $ chdodgemcontrol */
/* $ chdodgemdoors */
/* $ chdoor */
/* $ chdoormake */
/* $ chdoubloon */
/* $ chdragonbrothers */
/* $ chdrawbridgeswitches */
/* $ chdrips */
/* $ chdumbwaiterlift */
/* $ chdummyjigsaw */
/* $ cheel */
/* $ cheggclockwork */
/* $ cheggfire */
/* $ chegggolden */
/* $ chegggrenade */
/* $ cheggice */
/* $ cheggnormal */
/* $ cheggproximity */
/* $ cheggsplode */
/* $ chelectricfence */
/* $ chevilmumbo */
/* $ chevilspirit */
/* $ chexploder */
/* $ chexplodingchainlinks */
/* $ chfactorybattery */
/* $ chfactorybtwmdoor */
/* $ chfactorycrusher */
/* $ chfactorydrums */
/* $ chfactoryempspell */
/* $ chfactoryentrydoors */
/* $ chfactoryflypad */
/* $ chfactorygoblin */
/* $ chfactoryliftdoor */
/* $ chfactorylight */
/* $ chfactorylinkgrill */
/* $ chfactorylobbydoor */
/* $ chfactorymagnet */
/* $ chfactorymaindoor */
/* $ chfactoryposter */
/* $ chfactoryprop */
/* $ chfactoryrobot */
/* $ chfactoryroofbits */
/* $ chfactorysmoke */
/* $ chfactorysparkroom */
/* $ chfactorystationdoors */
/* $ chfactorytoxiccloud */
/* $ chfactorytoxicpools */
/* $ chfactorytrashbelt */
/* $ chfactorytwinklies */
/* $ chfactoryworkerdirty */
/* $ chfactoryworkerwear */
/* $ chfaircoin */
/* $ chfaircoinbox */
/* $ chfairgroundworker */
/* $ chfantasyathlete */
/* $ chfantasybounce */
/* $ chfantasycannon */
/* $ chfantasydrillfield */
/* $ chfantasyeyeball */
/* $ chfantasylakebits */
/* $ chfantasyonion */
/* $ chfantasysafe */
/* $ chfantasysafeswitch */
/* $ chfantasytrashcanbits */
/* $ chfirefx */
/* $ chfiregen */
/* $ chfireicestorm */
/* $ chfireimp */
/* $ chfishshootgame */
/* $ chflamer */
/* $ chfloater */
/* $ chfloaty */
/* $ chfloorbubbles */
/* $ chflowerbaddie */
/* $ chflysaucer */
/* $ chflysaucercrate */
/* $ chflysaucerdoor */
/* $ chfog */
/* $ chfoodwarn */
/* $ chfootwear */
/* $ chfpsgame */
/* $ chfreezy */
/* $ chfriendlystonehead */
/* $ chfriesstand */
/* $ chgameselect */
/* $ chgate1doors */
/* $ chghostdoor */
/* $ chglowbo */
/* $ chgobicommon */
/* $ chgobihailfire */
/* $ chgobiwitchy */
/* $ chgoldfish */
/* $ chgoldsnakehead */
/* $ chgoldstatue */
/* $ chgruntyfireball */
/* $ chgruntyfireballbig */
/* $ chgruntylairexttowerwindow */
/* $ chhagstraindoor */
/* $ chhagstraindoorswitch */
/* $ chhandcart */
/* $ chheggy */
/* $ chhellterskelter */
/* $ chhellterskeltermouth */
/* $ chhillbilly */
/* $ chhoney */
/* $ chhoneyb */
/* $ chhoneycarrier */
/* $ chhoopswoop */
/* $ chhotfloorsmoke */
/* $ chhotwaterpoolbits */
/* $ chhotwatersteam */
/* $ chhumba */
/* $ chicekey */
/* $ chicekeydoor */
/* $ chicestationbits */
/* $ chiciclebits */
/* $ chicywind */
/* $ chidgoldhorde */
/* $ chinflatableboss */
/* $ chinflatablebossdoor */
/* $ chintrocam */
/* $ chintrochar */
/* $ chintrotext */
/* $ chintroticker */
/* $ chjadesnake */
/* $ chjadestatue */
/* $ chjamjarsdummy */
/* $ chjellycastle */
/* $ chjiggybeam */
/* $ chjiggygamenew */
/* $ chjiggypost */
/* $ chjiggytemple */
/* $ chjigsaw */
/* $ chjigsawbitcont */
/* $ chjigsawcollect */
/* $ chjigsawdance */
/* $ chjinjo */
/* $ chjinjovillagecamera1 */
/* $ chjollyroger */
/* $ chjrinnlight */
/* $ chjujubagfx */
/* $ chkingjinjo */
/* $ chkingjinjobits */
/* $ chklungo */
/* $ chklungodoors */
/* $ chklungoforcefield */
/* $ chklungoleave */
/* $ chklungophial */
/* $ chklungospiral */
/* $ chlagoonbilldrillcover */
/* $ chlagoonbits */
/* $ chlagoonentrygate */
/* $ chlagoonfish */
/* $ chlagoonlockerdoorhits */
/* $ chlagoonpirate */
/* $ chlagoonufoext */
/* $ chlagoonufoint */
/* $ chlakemonster */
/* $ chlaundry */
/* $ chlavaarchgrill */
/* $ chlavaarchgrill3switches */
/* $ chlavaarchgrillswitch */
/*@oooo*/ AIDS *DLL_chlavaarchgrillswitch_00(void);
/* $ chlavacolumns */
/* $ chlavacolumnswitch */
/* $ chlavaentrancebridge */
/* $ chlavaentrancebridgeswitch */
/* $ chlavaentrydoor */
/* $ chlavaexplodbuild */
/* $ chlavafall */
/* $ chlavagargoyle */
/* $ chlavahand */
/* $ chlavaslab */
/* $ chlavaslabswitch */
/* $ chlavatraindoor */
/* $ chlavatraindoorswitch */
/* $ chlensflare */
/* $ chlifeforcespell */
/* $ chlightdemon */
/* $ chlightfader */
/* $ chlighthalo */
/* $ chlilterry */
/* $ chlinkpipefan */
/* $ chloggo */
/* $ chmadamegrunty */
/* $ chmasterjiggy */
/* $ chmayaentrydoor */
/* $ chmayafarmer */
/* $ chmermaidstatue */
/* $ chmineentrygrille */
/* $ chminegrill2switches */
/* $ chminegrilldoor */
/* $ chminelight */
/* $ chminelightswitch */
/* $ chminelobbydoor */
/* $ chmineproplight */
/* $ chmineprospector */
/* $ chminisubgame */
/* $ chmole_cuckoo */
/* $ chmole_factory */
/* $ chmole_hailfire */
/* $ chmole_lagoon */
/* $ chmole_maya */
/* $ chmole_mine */
/* $ chmole_overworld */
/* $ chmole_prehist */
/* $ chmole_training */
/* $ chmole_witchy */
/* $ chmolehill */
/* $ chmoley */
/* $ chmonsterinterior */
/* $ chmricecube */
/* $ chmrsboggy */
/* $ chmrsboggyhome */
/* $ chmrsicecube */
/* $ chmrtannoy */
/*@oooo*/ void DLL_chmrtannoy_00(void);
/* $ chmumbohealspell */
/* $ chmumbopad */
/* $ chmumbopadstatue */
/* $ chmumboskullfakearchpanellava */
/* $ chmumboskulls */
/* $ chmusicmenu */
/* $ chnastycavemen */
/* $ chnests */
/* $ chnewfreezy */
/* $ chnewmumbo */
/* $ chnewshovel */
/* $ chnicecavemen */
/* $ chnicecavemenguard */
/* $ chnutsnbolts */
/* $ choctopus */
/* $ choildrill */
/* $ chonearmbandit */
/* $ chpawnbroker */
/* $ chperspexbox */
/* $ chperspexboxswitch */
/* $ chphlegm */
/* $ chpickups */
/* $ chping */
/* $ chpiranha */
/* $ chplatuegrill */
/* $ chpodiumbankaz */
/* $ chpoolkids */
/* $ chpotogoldbits */
/* $ chpotogoldgame */
/* $ chpowerhut */
/* $ chpowerhutwitchy */
/* $ chprisonbits */
/* $ chproplighter */
/* $ chpufferfish */
/* $ chpumproomgrill */
/* $ chpumproomswitch */
/* $ chquicksandbaddy */
/* $ chquiz */
/* $ chquizexitdoor */
/* $ chquizremotectrl */
/* $ chrainbow */
/* $ chrainripples */
/* $ chsabreman */
/* $ chscorepoints */
/* $ chscreenadjust */
/* $ chseaweedbaddy */
/* $ chsecreteggs */
/* $ chshockjump */
/* $ chsignpost */
/* $ chsilo */
/* $ chskeletonexplode */
/* $ chsmalltrexdoor */
/* $ chsounder */
/* $ chsparkle */
/* $ chspiralgrill */
/* $ chspotlight */
/* $ chsquits */
/* $ chstadiumdoors */
/* $ chstarspinnerctrl */
/* $ chstarspinnerplanet */
/* $ chstarspinnerstar */
/* $ chstatictorch */
/* $ chstatueboss */
/* $ chstatuebossbits */
/* $ chstinger */
/* $ chstoneballcoach */
/* $ chstoneballcontrol */
/* $ chstonedartgunhead */
/* $ chstonepillar */
/* $ chsunlightspell */
/* $ chswampplatform */
/* $ chswappy */
/* $ chswitch */
/* $ chtalontorpedoboulder */
/* $ chtemplebossdoor */
/* $ chtemplebrokendoorpiece */
/* $ chtempleinternaldoor */
/* $ chtemplelobbydoor */
/* $ chterryegg */
/* $ chterryteeth */
/* $ chtimetable */
/* $ chtiptup */
/* $ chtntblockage */
/* $ chtntbox */
/* $ chtntdetonator */
/* $ chtnthut */
/* $ chtntminecelldoor */
/* $ chtntmineshoot */
/* $ chtoothyfish */
/* $ chtorpedo */
/* $ chtoxicroombits */
/* $ chtoxicroomprops */
/* $ chtransparencypot */
/* $ chtransparentfish */
/* $ chtrashcangame */
/* $ chtrashcompactor */
/* $ chufoextdoor */
/* $ chusefeather */
/* $ chvandoor */
/* $ chvolcanobits */
/* $ chwallsnakebaddy */
/* $ chwandglow */
/* $ chwarppad */
/* $ chwarriorbaddy */
/* $ chwaspnestgame */
/* $ chwaspstatue */
/* $ chwaterfallfx */
/* $ chwaterfallgrill */
/* $ chwaterfallgrillswitch */
/* $ chweather */
/* $ chweldarboss */
/* $ chweldarbossdoors */
/* $ chweldarbossfireball */
/* $ chweldarbossfusebox */
/* $ chweldarhead */
/* $ chwitchyentrygates */
/* $ chwitchyshockpadswitch */
/* $ chwitchytents */
/* $ chworlddoors */
/* $ chwumbawigwam */
/* $ chzubba */
/* $ cosection */
/*@o---*/ MAP DLL_cosection_00_get_dev_bootmap(void);
/*@oooo*/ MAP DLL_cosection_01_get_retail_bootmap(void);
/* $ cosectionstor */
/* $ cothemedll */
/* $ dbanim */
/* $ dbid */
/* $ dblight */
/* $ dbmorph */
/* $ dbpalette */
/*@oooo*/ void DLL_dbpalette_00(u32 *, u32, u32 *);
/*@oooo*/ void DLL_dbpalette_01(u32 *, u32, u32 *);
/* $ dbshift */
/* $ dbskeleton */
/* $ dbtex */
/* $ dbvpl */
/* $ dbvtxnormal */
/*@oooo*/ s32   DLL_dbvtxnormal_00(s32, s32);
/*@o---*/ void  DLL_dbvtxnormal_01(void *);
/*@o---*/ void *DLL_dbvtxnormal_02(s32 *);
/* $ dbzone */
/* $ fxairbub */
/* $ fxdialog */
/* $ fxdlsmoke */
/* $ fxegg */
/* $ fxfontstring */
/* $ fxgenlist */
/* $ fxkern */
/*@o---*/ void DLL_fxkern_00_totalsfont_print(Gfx **dl, s32 x, s32 y, char *str);
/*@oooo*/ void DLL_fxkern_01_totalsfont_print_centred(Gfx **dl, s32 y, char *str);
/*@oooo*/ void DLL_fxkern_02_totalsfont_size_reset(void);
/*@oooo*/ void DLL_fxkern_03_totalsfont_size_set(f32 size);
/* $ fxleaves */
/* $ fxmumbo */
/* $ fxrain */
/* $ fxripple */
/* $ fxsparkle */
/* $ fxspgold */
/* $ fxsplash */
/* $ fxsplash25d */
/* $ fxstep */
/* $ fxtwinkle */
/* $ gcaudiolist */
/* $ gcboundDll */
/* $ gccollectDll */
/* $ gccubeDll */
/* $ gccubesearch */
/* $ gcdialogDll */
/* $ gcdialogcamera */
/* $ gcdialogexec */
/* $ gcegg */
/* $ gcextra */
/* $ gcfrontend */
/* $ gcgame */
/* $ gcgamefix */
/* $ gcgoto */
/* $ gcintrotext */
/* $ gclevel */
/* $ gclightsDll */
/* $ gcmapDll */
/* $ gcmapsects */
/* $ gcmapsects_lagoonbot */
/* $ gcmapsects_lagoonmid */
/* $ gcmapsects_lagoontop */
/* $ gcnewoption */
/* $ gcnewpause */
/* $ gcsectionDll */
/* $ gcsectionskip */
/* $ gcskyDll */
/* $ gcstatusDll */
/* $ gctransitionDll */
/* $ gcwater */
/* $ gczoombox */
/* $ gczoomboxdata */
/* $ gemarkersDll */
/* $ glcrc */
/* $ glcutDll */
/* $ gldbDll */
/* $ gldbstring */
/* $ gldialog */
/* $ gleeprom */
/* $ glgamedata */
/* $ glgamestore */
/* $ glglobaldata */
/* $ glglobalsettings */
/* $ glhittableDll */
/* $ glid */
/* $ glidmake */
/* $ glintrosyncDll */
/* $ glpackvtx */
/* $ glrecord */
/* $ glreflight */
/*@oooo*/ u32 DLL_glreflight_00(void);
/* $ glrtc */
/* $ glsavegame */
/* $ glsplineDll */
/* $ glsplinecs */
/* $ glsplinefind */
/* $ glsplinefuncs */
/* $ glsplinenode */
/* $ glzone */
/*@oooo*/
/*@oooo*/
/*@oooo*/
/*@oooo*/
/*@oooo*/
/*@oooo*/ u8 DLL_glzone_05(s32, Vec3f *, u8);
/*@oooo*/
/* $ gsattract */
/* $ gsmaker */
/* $ gspropctrl */
/* $ gsproplookup */
/* $ gspropmarker */
/* $ gspropprop */
/* $ gspropsDll */
/* $ gsworldDll */
/* $ gzpublic */
/* $ gzreg */
/* $ gzthread */
/* $ gztrace */
/* $ idbounce */
/* $ idflame */
/* $ idflash */
/* $ idflasha */
/* $ idflashbaddie */
/* $ idglow */
/* $ idglowa */
/* $ idlight */
/* $ idscroll */
/* $ idtwinkle */
/* $ idtwinklea */
/* $ idtwinklecolour */
/* $ idwater */
/* $ idwave */
/* $ idwibble */
/* $ idworld */
/* $ idworldmake */
/* $ inantab */
/* $ indrv_audio */
/* $ indrv_fx */
/* $ indrv_lights */
/* $ mlspline */
/* $ mlwave */
/* $ ncba1p */
/* $ ncbabee */
/* $ ncbaclimb */
/* $ ncbadeflect */
/* $ ncbadie */
/* $ ncbadive */
/* $ ncbadolly */
/* $ ncbafixpos */
/* $ ncbafly */
/* $ ncbaglide */
/* $ ncbajig */
/* $ ncbakaztorp */
/* $ ncbaledge */
/* $ ncbapan */
/* $ ncbapivot */
/* $ ncbaspiral */
/* $ ncbaspline */
/* $ ncbastring */
/* $ ncbasub */
/* $ ncbasuck */
/* $ ncbaswim */
/* $ ncbatarget */
/* $ ncbawaypoint */
/* $ ncfixposrot */
/* $ ncpod */
/* $ ncpoddialog */
/* $ ncpodfixpos */
/* $ ncpoducam */
/* $ ncstart */
/* $ plcamera */
/* $ plsu */
/* $ rtlight */
/* $ sccustom */
/* $ sccustom_banjo */
/* $ sccustom_big */
/* $ scinfobar */
/* $ scradar */
/* $ seqdat */
/* $ seqdefine */
/* $ suautobaddies */
/* $ subaddie3d */
/* $ subaddieDll */
/* $ subaddieaudioloop */
/* $ subaddieaudioquick */
/* $ subaddiebounce */
/* $ subaddiecustomhits */
/* $ subaddiedialog */
/* $ subaddiedraw25d */
/* $ subaddiefade */
/* $ subaddiefind */
/* $ subaddiefx */
/* $ subaddieitem */
/* $ subaddiejoy */
/* $ subaddielink */
/* $ subaddiemarker */
/* $ subaddiemulti */
/* $ subaddiepalette */
/* $ subaddierouteDll */
/* $ subaddiesect */
/* $ subaddieskeleton */
/* $ subaddiestore */
/* $ subaddietaxi */
/* $ subaddievolume */
/* $ subaddiezone */
/* $ suchase */
/* $ sucoaster */
/* $ sucoasterdata */
/* $ sucoasterfly */
/* $ sucoasterflydata */
/* $ sucoasterhit */
/* $ sucoasterplayer */
/* $ sudeathmatch */
/* $ sudeflect */
/* $ sudialog */
/* $ suegg */
/* $ sueggmisc */
/* $ sueggmove */
/* $ suexpression */
/* $ suexpressjoint */
/* $ suexpressmorph */
/* $ sufade */
/* $ suflamefx */
/* $ sufreezy */
/* $ suinv */
/* $ sujiggy */
/* $ sukickball */
/* $ sulights */
/* $ sumissilehome */
/* $ sumole */
/* $ sumultiscore */
/* $ sumumbofx */
/* $ suquiz */
/* $ surestart */
/* $ suspline */
/* $ susplinet */
/* $ susubgame */
/* $ sutempleboss */
/* $ trangler */
/* $ vpflicker */
/* $ vpglow */
/* $ vplight */
/* $ vpmodule */
/* $ vpscroll */
/* $ vpwibble */




#endif // __DLLS_H__


