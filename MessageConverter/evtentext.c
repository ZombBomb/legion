//=============================================================================
//                       Hypercom Inc
//                      (c) Copyright 2003
//=============================================================================
//	Module overview:	evtentext.c
//	English event text table
//=============================================================================
#include "basictyp.h"
#include "sdk.h"
#include "sdkos.h"
#include "sdkmem.h"
#include "struct.h"
#include "appdata.h"
#include "xfunc.h"
#include "evttextinit.h"
#include "transdef.h"
#include <string.h>

//=============================================================================
// External variables / declarations
//=============================================================================

// Public functions defined in this module

// Public from other modules

//=============================================================================
// Private defines and typedefs
//=============================================================================


//=============================================================================
// Private function declarations
//=============================================================================


//=============================================================================
// Public data definitions
//=============================================================================

//====================================================
//===  ENGLISH EVENT MESSAGE TABLE                 ===
//====================================================

#ifdef MAKE_ENGLISH

static const char *const EvtEnText[] = {
	// NOOPT must be first entry in this table -- do not remove
	"",							// NOOPT
	"SALE",						// SALE
	"REVIEW",					// REVIEW
	"SETTLE",					// SETTLE
	"MERCH FUNC",				// FUNCTION
	"INITIALIZE",				// INITIALIZE
	"",							// DEBIT
	"FIND",						// FIND
	"ADJUST",					// ADJUST
	"BALANCE",					// BALINQ
	"REPRINT",					// REPRINT
	"VOID",						// VOIDTRAN
	"REPORTS",					// REPORTS
	"TOTALS",					// TOTALS
	"REFUND",					// REFUND
#ifdef MKSL
	"OFF-LINE",					// SALOFFL
#else
	"CHECKOUT",					// SALOFFL
#endif // MKSL
	"PRINT LIST",		// PRTLIST          Event Text
	"PRINT TILL",		// PRTTILL          Event Text
	"TEST",					// TESTTRAN         Event Text
	"AUTHORIZE",		// AUTH             Event Text
	"ADJUST SAL",		// ADJSALE          Event Text
	"ADJUST REF",		// ADJREFUND        Event Text
	"TRAIN MODE",		// TRAINMODE        Event Text
	"SETTLE",				// CLBATCH          Event Text
	"SETTLE",				// CLBATCHA         Event Text
	"SETTLE",				// CLBATCHE         Event Text
	"UPLOAD",				// RUPLOAD          Event Text
	"RESPONSE",			// LASTRSP          Event Text
	"CANCEL AUTH",							// VOIDAUTH
#ifdef BSRV
	"SALE + CASH",							// SALECASH
#else
	"SALE & CASH",							// SALECASH
#endif
	"",							// CHANGESHIFT_FUN  Event Text
	"",							// SETUP_FUN        Event Text
	"",							// SETDT_FUN        Event Text
	"",							// CASHIER_FUN      Event Text
	"",							// TESTTRAN_FUN     Event Text
	"",							// TESTPRT_FUN      Event Text
	"",							// TESTCRDR_FUN     Event Text
	"",							// RESET_FUN        Event Text
	"",							// PROGLD_FUN       Event Text
	"",							// TERMID_FUN       Event Text
	"",							// INITPHONE_FUN    Event Text
	"",							// INITNMS_FUN      Event Text
#ifndef MAKE_M2
	"",							// DIALTYPE_FUN     Event Text
	"",							// PABX_FUN         Event Text
	"",							// TERMALL_FUN      Event Text
	"",							// TERMSETUP_FUN    Event Text
#endif // MAKE_M2
	"",							// PRTENABLE_FUN    Event Text
	"",							// PAPERFEED_FUN    Event Text
	"",							// PSWDCHANGE_FUN   Event Text
	"",							// PSWDONOFF_FUN    Event Text
	"",							// COMM_FUN         Event Text
	"",							// SETCONTRAST_FUN  Event Text
	"",							// CLEAR_AQ_FUN     Event Text
	"",							// PRTH_FUN         Event Text
	"",							// INITR_FUN        Event Text
	"",							// TXRX_FUN         Event Text
	"",							// TESTDISP_FUN     Event Text
	"",							// TESTKYBD_FUN     Event Text
	"",							// PINPADVER_FUN    Event Text
	"",							// TERMVER_FUN      Event Text
	"",							// TESTPINPAD_FUN   Event Text
	"LOGON",				// LOGON            Event Text
	"ICEPAC",				// ICEPAK_DOWNLOAD  Event Text
	"",							// CLEAR_REV_FUN    Event Text
	"",							// CLEAR_ALL_FUN    Event Text
	"",							// SETTLE_STATUS_FUN Event Text
	"",							// SET_LANGUAGE     Event Text
#ifdef RUST
	"",							// SET_PRINTLANG     Event Text
	"SALE",						//SALEAUTH			Event Text
	"SALE",						//EMV_SALEAUTH		Event Text
#endif //RUST
#if defined (RUST) || defined (OWNATIVE) || defined (SMARTVISTA)
	"INSTALLMENT",				//INSTALMENT		Event Text
	"INSTALLMENT",				//EMV_INSTALMENT	Event Text
#endif // RUST || OWNATIVE || SMARTVISTA
	"CASH",					// CASH
	"CREDIT",				// CREDIT
	"",					 	// CURRENCY REPORT
#ifdef MOBI
	"CASHCREDIT",									// CREDVOUCHER
#else // MOBI
	"CREDIT VCH",	 		// CREDIT VOUCHER
#endif // MOBI

#if defined(SSBN)
	"MOTO/SOF",			// MAIL_ORDER
#else
	"MAIL ORDER",		// MAIL_ORDER       Event Text
#endif
	"",					// PLS_WAIT_ADVICE
	"BLOCKTERM",        // Block the terminal
	"MMODE",            // Change Mmode
	"SETPOS",			// SETPOS

#ifdef MAKE_STOPLIST
	"",							// SL_UPDATE
	"",							// SL_FULL
#endif // MAKE_STOPLIST

	"RS-232",				// RS232 OPTIONS
	"",						// RS232-work-around @nau

#ifdef GOODS
	"PRICE",				// Product price
	"BAN",					// Product ban
	"",							// Product list
	"",							// Product report
#endif //GOODS

#ifdef TOLL
	"MENU",					// Tariff menu
	"REPORT",				// Tariff report
	"",						// TOLL_SESSION
#endif // TOLL

	"SALE",				// EMV_SALE
	"CASH",			// EMV_CASH
	"CREDIT",			// EMV_CREDIT
	"REFUND",			// EMV_REFUND
	"BALANCE",			// EMV_BALINQ
	"FALLBK",			// EMV_FALLBACK
	"AUTHORIZE",				// EMV_AUTH
#ifdef MKSL
	"OFF-LINE",			// EMV_SALCOMP
#else
	"SALCOMP",			// EMV_SALCOMP
#endif // MKSL
#ifdef OPENWAY
	"VOIDAUTH",			// EMV_VOIDAUTH
	"LIMIT CARD",		// EMV_TOPUP
	"CARD LOG",			// EMV_LOGICC
	"BAL. OFFL",			// EMV_BALOFFL
	"UTIL PAYM",			// EMV_UTILPAYMENT
	"LIMIT CARD",		// EMV_TOPUPFULL
#ifdef MOBI
	"CASHCREDIT",									// EMV_CREDVOUCHER
#else // MOBI
	"CREDIT VCH",		//EMV_CREDVOUCHER
#endif // MOBI
#endif // OPENWAY
#if defined(MAKE_SV3) || defined (OPENWAY)
	"EMV INFO", 		// EMV_INFOADV
#endif // MAKE_SV3 || OPENWAY

#if defined (MAKE_P2100) || defined (TELIUM2)
	"",							// INITIPADR_FUN    Event Text
	"",							// INITPORT_FUN  Event Text
	"",							// INITSSLUSE_FUN Event Text
#endif // MAKE_P2100 || TELIUM2
#ifdef MAKE_P2100
//@nau {Ethernet support
	"",							// TERMINALIPADR_FUN Event Text
	"",							// IPTYPE_FUN Event Text
#ifdef MAKE_SV3
	"",							// TERMINALIPPORT_FUN Event Text
#endif	// MAKE_SV3
	"",							// SUBNETIPADR_FUN  Event Text
	"",							// GATEWAYIPADR_FUN Event Text
	"",							// NMSIPADR_FUN Event Text
	"",							// NMSPORT_FUN  Event Text
//@nau}
#endif
	"STATISTICS",				// STATISTICS		Event Text
#ifdef ARMI
	"VoiceAuth",				// VOICEAUTH
	"Confirm",					// CONFIRM
#endif // ARMI

#if defined( OPENWAY ) || defined( TPTP) || defined( TRANSMASTER )  || defined( HYPTS ) || defined( SMARTVISTA )
	"PAYMENT",						// PAYMENT
	"PAYMENT",						// EMV_PAYMENT
#endif	// OPENWAY || TPTP || defined( TRANSMASTER )  || defined( HYPTS ) || SMARTVISTA

#ifdef OWNATIVE
	"PAYMENT",					// PAYMENT_BYCASH
	"AUTH CASH",				// PREAUTHCASH
	"AUTH CASH",				// EMV_PREAUTHCASH
	"CASHBYCODE",				// CASHBYCODE
	"CASHTOCARD",				// CASHTOCARD
	"CASHTOCARD",				// EMV_CASHTOCARD
#endif // OWNATIVE

//@tav{
#ifdef TDBM
	"SALE",								// LOYSALE
	"REFUND",							// LOYREFUND
	"SALECOMP",							// LOYSALECOMP
	"SALE",								// PNTSALE
	"REFUND",							// PNTREFUND
	"VOID",								// PNTVOIDSALE
	"BALANCE",							// PNTBALANCE
#endif // TDBM
//@tav}
//@akuzm{
#ifdef OPENWAY
	"UTILPAYMENT",							// OPENWAY UTILITY PAYMENT
#endif	// OPENWAY
//@akuzm}

#ifdef MKSL	// MAKE_E_PREPAID
	"PRE-PAID",			// EPP_PIN
	"EPPSTCKDLD",		// EPP_STOCKDLD
	"EPP OFFL",			// EPP_SALOFFL
	"EPP CLBTCH",		// EPP_CLBATCH
	"EPP RUPLD",		// EPP_RUPLOAD
	"EPPCLBTCHE",		// EPP_CLBATCHE
	"",					// EPP_CLEAR_PIN
#endif	// MKSL // MAKE_E_PREPAID

//@svi{
	"",					// REVERSAL_TRAN
#ifdef MAKE_ECR
	"READ CARD",		// CARD_READ
	"READ CARD",		// EMV_CARD_READ
#endif // MAKE_ECR

//@svi}

	"",							// NOT_SUPPORTED
#if defined(MAKE_T2100)
    "",			// TRACE_START
    "",			// TRACE_STOP
    "",			// TRACE_PRINT
    "", 		// TRACE_SEND2
    "",			// TRACE_SEND1
#endif // MAKE_T2100
#if defined(OWNATIVE) && defined(MAKE_P2100) && defined(STDR)
	"",		// KEYIDCHANGE_FUN
#endif // STDOPO
#ifdef OWNATIVE
    "KEYCHANGE",				// 0x008C - key exchange
	"MINISTATE", //  MINISTATE
	"MINISTATE", //  EMV_MINISTATE
	"POSINIT",				// 0x008B - pos init
    "UNBLOCKPIN",			// 0x008D - unblock pin
    "UNBLOCKAPP",			// 0x008E - unblock application
#endif // OWNATIVE
#if defined(OWNATIVE) || defined(TPTP)
	"CHANGE PIN",			// CHANGE_PIN
	"CHANGE PIN",			// EMV_CHANGE_PIN
#endif // OWNATIVE || TPTP
#ifdef OWNATIVE
	"VOID CREDIT",			// VOIDCREDIT
	"VOID CREDIT",			// VOIDCREDIT
#endif // OWNATIVE
#ifdef BSRV
	"SALE + CASH",							// EMV_SALCASH
#else
	"SALE&CASH",							// EMV_SALCASH
#endif
#if defined(MAKE_P2100) || defined (TELIUM2)
	"",			// SETNII_FUN
#endif // MAKE_P2100 || MAKE_H2200 || TELIUM2
#if defined(MAKE_P2100) || defined(VERIFONE) || defined(PAXPROLIN)
	"",			// HKLMKEYLOAD
#endif // MAKE_P2100 || VERIFONE || PAXPROLIN
#ifdef MAKE_P2100
	"",			// LINETYPE_FUN
#endif // MAKE_P2100
#if defined(MAKE_SV3) && !defined(MAKE_OPTIMUM)
	"",         // SV3SETUP_FUN
#endif // MAKE_SV3 && !MAKE_OPTIMUM
#ifdef MAKE_P2100
	"",         // SHOWBKCV_FUN
	"",			// SHOWMKCV_FUN
#if defined( ALFA )
	"",			// TOGGLE_MANUAL_PAN
#endif
#if defined( RUST )
	"",			// RM_TIMESYNC_FUN
#endif
#endif //MAKE_P2100
#ifdef OPENWAY
	"",			// SET_BATCH_NUM
#endif // OPENWAY
#if defined(MAKE_ECR) || defined(MAKE_SV3)
	"",			// CONNECT_ECR
#endif // defined(MAKE_ECR) || defined(MAKE_SV3)
#ifdef MAKE_SV3
	"",			// SERVICE_ECR
	"",			// UNSUPPORTED
	"",			// CLEAR_ECR
#endif // MAKE_SV3
#ifdef MAKE_MULTIAPP
	"",			// CHANGE_APP
#endif	// MAKE_MULTIAPP
#if defined(TPTP) || defined(OWNATIVE)
	"PREP. CODE",				// PREPAID_CODE
	"PREP. CODE",			// EMV_PREPAIDCODE
#endif //
#if defined(TPTP) || defined(COMPASS)
	"P2P CARD",					// P2PCARD
	"P2P CASH",					// P2PCASH
	"P2P CALCFEE",				// P2PCALCFEE
	"P2P CARD",			// EMV_P2PCARD
	"P2P CASH",			// EMV_P2PCASH
	"P2P CALCFEE",			// EMV_P2PCALCFEE
#endif // TPTP || COMPASS
#if defined(TPTP) || defined(SPDH)
	"",						// DOWNLOADREQ
	"",						// PARTDOWNLOADREQ
	"CLOSEBATCH",			// CLOSEBATCH
	"CLOSESHIFT",			// CLOSESHIFT
	"CLOSEDAY",				// CLOSEDAY
	"",						// TOTALSBATCH
	"",						// TOTALSSHIFT
	"",						// TOTALSDAY
	"LOAD KEYS",			// KEYDOWNLOADREQ
#endif // defined(TPTP) || defined(SPDH)
#if defined(TPTP) || defined(HYPTS)
	"QUASICASH",			// QUASICASH
	"QUASICASH",			// EMV_QUASICASH
#endif // defined(TPTP) || defined(HYPTS)
#ifdef TPTP
#if !defined (HYPERCOM)
	"ACCUM BONUS",			// ACCUM_BONUS
	"REDEEM BON.",			// REDEEM_BONUS
#endif // !HYPERCOM
	"",						// FILEDOWNLOADREQ
	"CARDVERIFY",			// EMV_CARDVERIFY
	"CARD VERIF.",			// CARDVERIFY
	"TELEBANK",				// TELEBANK
	"TELEBANK",				// EMV_TELEBANK
	"INSTITUTION",          // INSTITUTION
	"INSTITUTION",          // EMV_INSTITUTION	
	"",						// EMV_ADJUST
#endif // TPTP
	"",			// LOGOFF
#if defined( GAZP ) || defined( GAZB )
	"SLIP TRAN",					// SLIP_TRAN
#endif //GAZP || GAZB
#if defined (TRANSMASTER) || defined(TPTP)
	"STATEMENT",			// STATEMENT
	"STATEMENT",			// EMV STATEMENT
#endif // TRANSMASTER || TPTP
#ifdef MAKE_NMS
	"NMS",	                    // NMSDL
#endif // MAKE_NMS
	"",							// TESTHFS
#ifdef MAKE_HSM
	"",			// HSM_KEY_LOAD
#endif // MAKE_HSM
	"REFERRAL",			// REFERRAL
#if defined( SMARTVISTA ) || defined( TPII_ISO )
	"",					// UPDPINKEY
	"",					// UPDMACKEY
	"",					// NETCUTOVER
	"",					// NETCUTOVERA
#endif // SMARTVISTA || TPII_ISO
#ifdef SMARTVISTA
#ifdef USIB
	"",                 // SVLOADPINMK
	"",                 // SVLOADMACMK
	"",                 // SVLOADALLMK
	"",                 // SVCONFMK
#endif	// USIB
#ifdef GAZP
	"TRANSFER",         // TRANSFER
	"TRANSFER",         // EMV_TRANSFER
#endif // GAZP
#endif // SMARTVISTA

#ifdef MAKE_OWNLOYALTY
	"RETAIL CASH",		//RETAILCASH
	"RETAIL CASH",		//EMV_RETAILCASH
#endif //MAKE_OWNLOYALTY

#ifdef MOBI
	"ACT.SERVICE",		//CLIENT_LOGIN
	"ADD CARD",			//CARD_LOGIN
	"PHONE PAYM",		//PHONE PAYMENT
	"PASSWORDS",		//ONE-TIME PASSWORDS
	"PAY. LCARD",		//PAY_LOYCARD
	"PAYM.CONF",		//PAY_CONFIRM
	"PAY. LID",			//PAY_BY_LID
	"ACTIVATION",		//ACTIVATION
	"ACCOUNTING",		//SUM_ACCOUNTING
	"DISCOUNT",			//CURRENT_DISCOUNT
	"LOY.CREDIT",		// LOYCREDITWITHCARD
	"REMOTE SRV",		//REMOTE SERVICE
	"ACT.SERVICE",		//EMV_CLIENTLOGIN
	"ADD CARD",			//EMV_CARDLOGIN
	"PHONE PAYM",		//EMV_PHONE PAYMENT
	"PASSWORDS",		//EMV_ONE-TIME PASSWORDS
	"PAY. LCARD",		//EMV_PAYLOYCARD
#endif // MOBI
#if defined (KAZK) && defined (OWNATIVE)
	"TAX PAYMENT",		 // Tax Payment
#endif	// KAZK	 && OWNATIVE
#if defined( CYBERPLAT )
	"PAYMENT",	// CYBPPAYMENT
	"PAYMENT",	// EMV_CYBPPAYMENT
#endif // CYBERPLAT

#ifdef MAKE_XLS_THIN
	XLS_THIN_NAME" TRAN",			// XLS_XLSTRX
	XLS_THIN_NAME" INIT",         // XLS_INIT
	"",					// XLS_CANCELRETRY
	XLS_THIN_NAME" PING",         // XLS_PING
	XLS_THIN_NAME" INFO",         // XLS_GETINFO
	XLS_THIN_NAME" CARD",			// XLS_CARDBALANCE
	XLS_THIN_NAME" CANCEL",		// XLS_CANCEL
	XLS_THIN_NAME" VOID",			// XLS_VOID
	XLS_THIN_NAME" REFUND",		// XLS_REFUND
	"",					// XLS_DRAWMAINMENU
	"", 				// XLS_ADVICE
	"",					// XLS_EMV_XLSTRX
	"",					// XLS_EMV_CARDBALANCE
	"",					// XLS_EMV_REFUND
#if defined (RUST) || defined (MKSL)
	XLS_THIN_NAME" PARAMS",	//XLS_USER_PARAMS
#endif // RUST || MKSL
#ifdef RUST
	XLS_THIN_NAME" CARD",		// XLS_POSTBALANCE,
#endif // RUST
#ifdef MKSL
	"XLS TOTALS",  //XLS TOTALS
#endif // MKSL
#endif	// MAKE_XLS_THIN
#ifdef RUST
	"SALE/SOF",			// SALE_SOF
	"AUTH/SOF",			// AUTH_SOF
	"FORCE/SOF",		// FORCE_SOF
#endif // RUST
#if defined(MAKE_SV3) || defined(MAKE_ECR)
	"PING", 			//ECR_PNG
#endif //MAKE_ECR, MAKE_SV3
#if defined (MKSL) && !defined (MAKE_VIKING)
	"", 				// PRINT_AQUIRER
#endif // MKSL && !MAKE_VIKING
#if defined( RUST ) || defined( NBKG )
	"PAYMPRE",			// PAYMPRE
	"PAYMPRE",			// EMV_PAYMPRE
	"PAYMFIN",			// PAYMPRE
	"PAYMFIN",			// EMV_PAYMFIN
#endif //RUST || NBKG
#ifdef RUST
	"TELE ORDER",		// TELE_ORDER       Event Text
#endif // RUST
#if defined (MKSL) || defined (BSRV)
	"VERIFY",					// VERIFY           	Event Text
	"VERIFY",					// EMV_VERIFY       	Event Text
#endif // MKSL || BSRV
#ifdef MKSL
	"LYLDISCNT",				// LOYDISCOUNT      	Event Text
	"LYLDISCNT",				// EMV_LOYDISCOUNT      Event Text
	"CSDDPAY",					// CSSD Payment
	"CSDDPAY",					// CSSD Payment
#endif //MKSL
#ifdef MAKE_MULTIMERCH
	"",							// MERCHANT_UNLOAD
#endif // MAKE_MULTIMERCH
#ifdef MAKE_FEP
	"", 						// FEP_KEYCHANGE
#endif // MAKE_FEP
#ifdef GIFTPM
	"",							// PM_SALE
	"",							// PM_VOIDSALE
	"",							// PM_BALANCE
	"",							// PM_AUTH
	"",							// PM_VOIDAUTH
	"",							// PM_REFUND
	"",							// PM_VIRT_SALE
	"",							// PM_VIRT_CHECKAUTH
	"",							// PM_VIRT_AUTH
#endif // GIFTPM
#ifdef RUST
	"GIFTACTIV",				// GIFTTRAN
	"GIFTACTIV", 				// GIFTACTIV
	"GIFTACTIV", 				// GIFTCREDIT
	"CREDIT",					// CREDITFLEX
#endif // RUST
#ifdef MAKE_EPOS
	"",							// EPOS_FUNC
	"",							// JRN_FUNC
#endif // MAKE_EPOS
#ifdef MAKE_TSP_HOST
	"",							// TSPLUS_DRAWMAINMENU
	"TESTTRAN",					// TSPLUS_TESTTRAN
	"FILELOAD",					// TSPLUS_FILELOAD
#ifdef MAKE_TSP_UPDATES
	"INFO ADV",					// TSPLUS_INFOADV
#endif // MAKE_TSP_UPDATES
#ifdef MAKE_SAMLIC
	"LIC.RELOAD",				// TSPLUS_LICLOAD
#endif // MAKE_SAMLIC
#ifdef MAKE_TSP_LOYALTY
	"LOYALTY",					// TSPLUS_LOYALTY
	"LOYALTY",					// TSPLUS_LOYUPD
	"SETTLE",					// TSPLUS_SETTLE
	"TSL REFUND",				// TSPL_LOY_REFUND
#endif // MAKE_TSP_LOYALTY
#endif // MAKE_TSP_HOST
#ifdef MAKE_FR
	"",							// FR_SETRS232
#endif // MAKE_FR
#ifdef MAKE_MULTIMERCH
	"SETTLE ALL",				// SETTLEALL
#endif // MAKE_MULTIMERCH
#if defined(OWNATIVE) || defined(CTLA)
	"SET PIN",					// SET_PIN
	"SET PIN",					// EMV_SET_PIN
#endif // OWNATIVE || CTLA
#ifdef CFT
	"KEY LOAD",					// CFT_KEYSDOWNLOAD
	"",							// CFT_RUPLOAD
#endif // CFT
#ifdef MAKE_EPOS
	"",							// VER_FUNC
#endif // MAKE_EPOS
#ifdef HYPTS
	"FROM CARD",				// P2P_AUTH,
	"FROM CARD",				// P2P_VERIFY
	"FROM CARD",				// EMV_P2P_AUTH
	"FROM CARD",				// EMV_P2P_VERIFY
#endif // HYPTS
#ifdef USEM
	"REFUND",			// AWARD transaction
	"SALE",				// REDEEM transaction
	"BALANCE",			// PNTBALANCE transaction
#endif
#if !defined(HYPERCOM)
	"",							// SET_INIT_PARAM
	"",							// FILE_PRINTER_MENU_FUN
#endif // !HYPERCOM
#if defined (TELIUM2) && defined (_DEBUG)
	"",							// KEYS_CLEANUP_FUN
#endif // defined (TELIUM2) && defined (_DEBUG)
#ifdef MAKE_TAX
	"ON-TOP", //TAX_SALE
	"ON-TOP", //EMV_TAX_SALE
	"ON-TOP2", //TAX_SALE2
	"ON-TOP2", //EMV_TAX_SALE2
#endif // MAKE_TAX
#ifdef MAKE_GC
	"", 						// GC_REFILL
#endif // MAKE_GC
#if defined (MKSL) && !defined (MAKE_VIKING)
	"",					// PROFILE_REPORT
	"",					// CONFIG_REPORT
	"DIAGNOSTICS",	 //DIAGNOST_REPORT
#endif // MKSL && !MAKE_VIKING
#ifdef MAKE_SELECT_GPRS_APN
	"",							// CREATE_GPRS_APN
	"",							// SELECT_GPRS_APN
#endif // MAKE_SELECT_GPRS_APN
#ifdef MAKE_XLS_THIN
	"",							//XLS_BONUSSALE
#endif // MAKE_XLS_THIN
#if defined (CTLA) && defined (MAKE_BITMAP128)
	"",							//VOIDPARTIAL
#endif // CTLA && MAKE_BITMAP128
#ifdef MAKE_TIETO_KEYLOAD
	"PIN MK",					// CHNGPINMK
	"PIN WK",					// CHNGPINWK
	"EPIN MK",					// CHNGEPINMK
	"EPIN WK",					// CHNGEPINWK
	"",							// CLEAR_KLSTAT_FUN
#endif // MAKE_TIETO_KEYLOAD
#if defined(RUST) && defined(MAKE_OPTIMUM) && !defined(MAKE_M2)
	"WM PAYMENT",				// WEBMONEYPAY
	"WM REFUND",				// WEBMONEYREF
	"WM VOID",					// WEBMONEYVOID
	"u-CREDIT",         // CREDITREQ
	"VOID",						// CREDITREQVOID
	"u-CREDIT",					// CREDITCONFIRM
	"u-VOID",					// CREDITVOIDEOD
	"SETTLE",					// RSBISO_SETTLE
	"u-DEPOSIT",				// CREDITBALANCE
	"u-DEPOSIT",				// CREDITDEPOSIT
#endif // RUST && MAKE_OPTIMUM && !MAKE_M2
#ifdef MAKE_VIVOUPD
	"UPD. "VIVO_NAME,			// UPDATEVIVO
#endif // MAKE_VIVOUPD
#if defined (MAKE_BCR) && defined (MKSL)
	"RIGAS DOME",				// BRCD_PAYMPRE
	"RIGAS DOME",				//EMV_BRCD_PAYMPRE
	"RIGAS DOME",				//BRCD_PAYMADV
	"RIGAS DOME",				//EMV_BRCD_PAYMADV
#endif // MAKE_BCR && MKSL
#if defined (MAKE_XLS_THIN) && defined (MAKE_EUROTRANSIT)
	"XLS SETTLE",				// XLS_SETTLE
#endif // MAKE_XLS_THIN && MAKE_EUROTRANSIT
#ifdef HYPTS
	"BY CASH",					// C2C_AUTH
	"BY CASH",					// EMV_C2C_AUTH
	"BY CASH",					// C2C_VERIFY
	"BY CASH",					// EMV_C2C_VERIFY
#endif // HYPTS
#ifdef MAKE_ENH_PREAUTH
#ifdef MKSL
	"CANCEL AUTH",				// PARTIALVOIDAUTH
#else
	"PARTIALVOI",				// PARTIALVOIDAUTH
#endif // MKSL
#endif // MAKE_ENH_PREAUTH
	"",							// INTRNL_LOG
#if !defined(HYPERCOM) && !defined(VERIXVX)
	"",							// UPDATE_LOG
#endif // !HYPERCOM && !VERIXVX
#ifdef APDK
	"APDK INIT",				// APDKINIT
	"X-REPORT",					// APDKXREPORT
	"APDK SALE",				// APDKSALE
	"APDKREFUND",				// APDKREFUND
	"APDKBALANC",				// APDKBALANCE
	"APDKSETTLE",				// APDKSETTLE
	"APDK VOID",				// APDKVOID
#endif // APDK
#ifdef MAKE_TIETO_KEYLOAD
	"MAC MK",					// CHNGMACMK
	"MAC WK",					// CHNGMACWK
#endif // MAKE_TIETO_KEYLOAD
#ifdef MAKE_RFR_EXTTRAN
	"",							// RFR_DEFAULT_TRAN
#endif // MAKE_RFR_EXTTRAN
#ifdef MAKE_USSD
	"",							// SET_USSDNUMBER
	"",							// USSDBALINQ
#endif // MAKE_USSD
#ifdef MAKE_PREPAIDLV
	"PREPAID",				// PREPAIDLV
#endif // MAKE_PREPAIDLV
#if defined(VERIFONE) && !defined(TKLD)
	"",							// DISABLE_SRV_SSL
#endif //VERIFONE && !TKLD
#ifdef MAKE_AFD
	"SALE",					// AFD START Transaction
	"SALE",					// AFD EMV START Transaction
	"SALE",					// AFD FINISH Transaction
#endif // MAKE_AFD
#ifdef TRANSMASTER
	"",							// UPLOAD_START
#endif // TRANSMASTER
#ifdef MKSL
	"INSURANCE",				// INSURANCE
	"INSURANCE",				// EMV_INSURANCE
#endif // MKSL
#if defined (TPTP) && !defined (HYPERCOM)
	"ACCUM BONUS",				// EMV_ACCUM_BONUS
	"REDEEM BON.",				// EMV_REDEEM_BONUS
#endif // TPTP && !HYPERCOM
#if defined(MAKE_CM_INIT)  && defined(MAKE_MULTI_TMS)
	"",							// SET_TMSTYPE
#endif // MAKE_CM_INIT && MAKE_MULTI_TMS
#ifdef TKLD
	"",							// HKLMKEYLOAD_HSM
#endif // TKLD
#if defined (MAKE_TSP_KDH)
	"",                         // KDH_POS_CRT_REQ
	"",                         // KDH_CRT_EXCH
	"",                         // KDH_KEYS_REQUEST
	"",                         // KDH_KEYLOAD_STATUS
#endif // MAKE_TSP_KDH
#if defined (MAKE_TSP_KDH_SERVER)
	"",                         // KDH_SERVER_TRAN
	"",                         // KDH_POS_CRT_RSP
	"",                         // KDH_SEND_KED_CRT
	"",                         // KDH_ADD_PROD_CRT
	"",                         // KDH_REENCRYPT_KEYS
	"",                         // KDH_POS_SAM_CRT_RSP
#endif // MAKE_TSP_KDH_SERVER
#ifdef PKKHOST
	"",					// RUPLOAD_REV
	"",					// PKK_KEYLOAD
	"",					// KEY_UPDATERSP
	"",					// KEY_EXCHINITREQ
	"",					// SIGNVERIFY
	"",					// SUBPROTSELECT
	"",					// PKK_INIT2
	"",					// INIT2_PARAMSTATUS
	"",					// PKK_SLLOAD
#endif //PKKHOST
#ifdef COFE
	"V AUTH",					// VENDAUT
	"V AUTH",					// EMV_VENDAUT
#endif // COFE
#if defined (OPENWAY) || defined (TRANSMASTER)
	"OFFLSALE",                                              // OFF-LINE SALE
#endif	// OPENWAY || TRANSMASTER
};

//=============================================================================
// Private data definitions
//=============================================================================


//=============================================================================
// Public function definitions
//=============================================================================

//-----------------------------------------------------------------------------
//  EvtTextEn_Init      Add English Event table for DML support
//
//  Parameters:         None
//
//  Global Inputs:
//
//  Returns:            None
//
//  Notes:
//
//-----------------------------------------------------------------------------
extern bool WrongTableSizeStub(void);
extern void EvtTextEn_Init( void )
{
	short pgnum;

	// Verify the number of messages match
	if( END_OF_EVENTS == ( sizeof( EvtEnText ) / sizeof( EvtEnText[0] ) ) || WrongTableSizeStub())
	{
		// Get our page number
		pgnum = SDK_ThisPage(  );

		// Put text table EvtEnText into database
		TextIndexAddTable( evttext_table_id, LNG_EN, EvtEnText, pgnum );
	}
}
#endif // MAKE_ENGLISH
