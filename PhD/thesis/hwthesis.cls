\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{hwthesis}[2005/03/16 v0.3 Heriot-Watt Thesis Class]

\newif\ifcrest
\crestfalse

\DeclareOption{crest}{
  \cresttrue
}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{report}}
\ProcessOptions\relax


\LoadClass[a4paper,12pt]{report}
\ifcrest
\RequirePackage{graphicx}
\fi

\newcommand{\crestfile}{crest.eps}

\renewcommand{\baselinestretch}{1.5}

%% There must be a better way to do this!!

% This is really 1.5in because LaTeX is mad!
\setlength{\oddsidemargin}{0.5in}
% Right margin to 0.75in (A4 is 8.27in wide)
\setlength{\textwidth}{\paperwidth}
\addtolength{\textwidth}{-\oddsidemargin}
\addtolength{\textwidth}{-1in}
\addtolength{\textwidth}{-0.75in}
% Top margin to 0.75in
\setlength{\topmargin}{-0.25in}
% Size of the header
\setlength{\headheight}{0.5in}
% Distance from header to text
\setlength{\headsep}{0.1in}
%Size of the bottom to page to be 0.75in up (possibly broken)
\setlength{\footskip}{1.0in}
\addtolength{\footskip}{-12pt}
% Bottom margin to 0.4in
\setlength{\textheight}{\paperheight}
\addtolength{\textheight}{-1in}
\addtolength{\textheight}{-\topmargin}
\addtolength{\textheight}{-\headheight}
\addtolength{\textheight}{-\headsep}
\addtolength{\textheight}{-\footskip}
\addtolength{\textheight}{-0.4in}
% space out the eqnarrays more
\setlength{\jot}{0.5cm}

% Renew the title page to include the declaration
\renewcommand\maketitle{\begin{titlepage}%
    \let\footnotesize\small
    \let\footnoterule\relax
    \let \footnote \thanks
    \null\vfil
    \begin{center}
      {\large {\sc Heriot-Watt University}}\par
      \vskip 5\p@
      \ifcrest
      \includegraphics[height=100\p@]{\crestfile}
      \vskip -45\p@
      \else
      \vskip 60\p@
      \fi
      {\bf {\LARGE \@title \par}}%
      \vskip 3em%
      {\large
        \lineskip .75em%
        \begin{tabular}[t]{c}%
          \@author
        \end{tabular}\par}%
      \vskip 1.5em%
      {\large \@date \par}%       % Set date in \large size.
      \vskip 1.5em%
      %Submitted for the degree of Philosophi\ae{} Doctor in Mathematics
      {\sc Submitted for the degree of\par Doctor of Philosophy in
        Mathematics\par on completion of research in the\par Department of
        Mathematics,\par School of Mathematical and Computing Sciences.}
    \end{center}\par
    \vskip 50\p@
    \noindent
    This copy of the thesis has been supplied on the condition that anyone who
    consults it is understood to recognise that the copyright rests with the
    author and that no quotation from the thesis and no information derived
    from it may be published without the written consent of the author or the
    University (as may be appropriate).
    \@thanks
    \vfil\null
  \end{titlepage}%
  \if@titlepage
  \titlepage
  \null\vfil
  \@beginparpenalty\@lowpenalty
  \begin{center}%
    \bfseries Declaration
    \@endparpenalty\@M
  \end{center}
  I hereby declare that the work presented in this thesis was carried out by
  myself at Heriot-Watt University, except where due acknowledgement is made,
  and not been submitted for any other degree.
  \vskip 50\p@
  \noindent
  Signature of \@author:
  \vskip 50\p@
  \noindent
  Signature of Supervisor:
  \par\vfil\null\endtitlepage
  \else
  \if@twocolumn
  \section*{Declaration}%
  \else
  \small
  \begin{center}%
    {\bfseries Declaration\vspace{-.5em}\vspace{\z@}}%
  \end{center}%
  \quotation
  \fi
  I hereby declare that the work presented in this thesis was carried out by
  myself at Heriot-Watt University, except where due acknowledgement is made,
  and not been submitted for any other degree.
  \vskip 50\p@
  \noindent
  Signature of \@author:
  \vskip 50\p@
  \noindent
  Signature of Supervisor:
  \if@twocolumn\else\endquotation\fi
  \fi
  \setcounter{footnote}{0}%
  \global\let\thanks\relax
  \global\let\maketitle\relax
  \global\let\@thanks\@empty
  \global\let\@author\@empty
  \global\let\@date\@empty
  \global\let\@title\@empty
  \global\let\title\relax
  \global\let\author\relax
  \global\let\date\relax
  \global\let\and\relax
}
